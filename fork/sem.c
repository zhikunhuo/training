#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>

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

int main(void)
{
    pid_t result;
    int sem_id;

    /* create sem*/
    sem_id = semget(ftok(".", 'a'), 1, 0666|IPC_CREAT);

    /* init sem */
    init_sem(sem_id, 0);

    result = fork();
    if (result == -1)
    {
        perror("Fork\n");
    }
    else if(result == 0)
    {
        printf("Child process will wait for some seconds... \n");
        sleep(3);
        printf("The returned value is %d in the child process(PID = %d)\n", result, getpid());
        sem_v(sem_id);
    } else
    {
        sem_p(sem_id);
        printf("The return value is %d in the father process(PID = %d)\n", result, getpid());
        sem_v(sem_id);
    }

    exit(0);
}
