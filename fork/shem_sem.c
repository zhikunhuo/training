#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 2048

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


int init_sem(int sem_id, int init_value)
{
    union semun sem_union;

    sem_union.val = init_value;
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
        perror("Initialize semaphore");
        return -1;
    }

    return 0;
}


int del_sem(int sem_id)
{
    union semun sem_union;
    
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        perror("Delete semaphore");
        return -1;
    }

}


int sem_p(int sem_id)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;

    if (semop(sem_id, &sem_b, 1) == -1)
    {
        perror("P operation fail");
        return -1;
    }

    return 0;
}

int sem_v(int sem_id)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;

    if (semop(sem_id, &sem_b, 1) == -1)
    {
        perror("V operation");
        return -1;
    }

    return 0;
}

int ignore_signal(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGSTOP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int main()
{
    pid_t pid;
    char *shm_addr;
    char flag[] = "WROTE";
    char *buff;
    int shmid, semid;

    ignore_signal();

    semid = semget(ftok(".", 'a'), 1, 0666 | IPC_CREAT);
    init_sem(semid, 1); 

    /*create share memory*/
    if ((shmid = shmget(ftok(".", 'b'), BUFFER_SIZE, 0666 | IPC_CREAT)) < 0)
    {
        perror("Shmget");
        exit(1);
    } else {
        printf("Create share memory: %d\n", shmid);
    }



    pid = fork();
    if ( pid == -1)
    {
        perror("fork");
        exit(1);
    } else if (pid == 0)
    {
       sleep(1); 
        /*map share memory*/
        if ((shm_addr = shmat(shmid, 0 , 0)) == (void *) -1)
        {
            perror("Child: shmat");
            exit(1);
        } else
        {
            printf("Child: Attach share memory: %p\n", shm_addr);
        }
        
        do {
            sem_p(semid);
            if (strncmp(shm_addr, "quit", 4) == 0)
            {
                sem_v(semid);
                break;
            }
            
            printf("Child: get from father: %s\n", shm_addr);

            memset(shm_addr, 0, BUFFER_SIZE);
            sem_v(semid);
        } while(1);


        /* delet memory map*/
        if ((shmdt(shm_addr)) < 0)
        {
            perror("Shmdt");
            exit(1);
        } else {
            printf("Child: Dettach share memory\n");
        }

        sleep(5);
        /*Delete share memory */
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("Child: shmctl(IPC_RMID)\n");
            exit(1);
        } else {
            printf("Delete share memory\n");
        }


    } else {
        /* map share memory */
        if ((shm_addr = shmat(shmid, 0, 0) ) == (void *) -1)
        {
            perror("Parent: shmat");
            exit(1);
        } else {
            printf("Parent :Attach shared memory :%p\n", shm_addr);
        }

        do {
            sem_p(semid);
            printf("n Input some string:\n");
            if (fgets(shm_addr, BUFFER_SIZE, stdin) == NULL)
            {
                perror("fgets");
                sem_v(semid);
                break;
            }

            if (strncmp(shm_addr, "quit", 4) == 0)
            {
                sem_v(semid);
                break;
            }

            sem_v(semid);
         } while(1);

        /* Delete share memory map */
        if ((shmdt(shm_addr)) < 0)
        {
            perror("Parent: shmdt");
            exit(1);
        } else {
            printf("Parent: Deattach share memory\n");
        }
       
        waitpid(pid, NULL, 0);
        printf("Finished \n");
    }
    exit(0);
}
