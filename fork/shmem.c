#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 2048

int main()
{
    pid_t pid;
    int shmid;
    char *shm_addr;
    char flag[] = "WROTE";
    char *buff;

    /*create share memory*/
    if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666)) < 0)
    {
        perror("Shmget");
        exit(1);
    } else {
        printf("Create share memory: %d\n", shmid);
    }


    /* show share memory */
    system("ipcs -m");

    pid = fork();
    if ( pid == -1)
    {
        perror("fork");
        exit(1);
    } else if (pid == 0)
    {

        /*map share memory*/
        if ((shm_addr = shmat(shmid, 0 , 0)) == (void *) -1)
        {
            perror("Child: shmat");
            exit(1);
        } else
        {
            printf("Child: Attach share memory: %p\n", shm_addr);
        }

        system("ipcs -m");


        /* check memory head */
        while(strncmp(shm_addr, flag, strlen(flag)))
        {
            printf("Child: Wait for enable data ...\n");
            sleep(5);
        }

        /*Get data*/
        strcpy(buff, shm_addr + strlen(flag));
        printf("Child: Share memory :%s\n", buff);

        /* delet memory map*/
        if ((shmdt(shm_addr)) < 0)
        {
            perror("Shmdt");
            exit(1);
        } else {
            printf("Child: Dettach share memory\n");
        }

        system("ipcs -m");

        /*Delete share memory */
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("Child: shmctl(IPC_RMID)\n");
            exit(1);
        } else {
            printf("Delete share memory\n");
        }

        system("ipcs -m");

    } else {
        /* map share memory */
        if ((shm_addr = shmat(shmid, 0, 0) ) == (void *) -1)
        {
            perror("Parent: shmat");
            exit(1);
        } else {
            printf("Parent :Attach shared memory :%p\n", shm_addr);
        }

        sleep(1);
        printf("n Input some string:\n");
        fgets(buff, BUFFER_SIZE, stdin);
        strncpy(shm_addr + strlen(flag), buff, strlen(buff));
        strncpy(shm_addr, flag, strlen(flag));

        /* Delete share memory map */
        if ((shmdt(shm_addr)) < 0)
        {
            perror("Parent: shmdt");
            exit(1);
        } else {
            printf("Parent: Deattach share memory\n");
        }

        system("ipcs -m");

        waitpid(pid, NULL, 0);
        printf("Finished \n");
    }
    exit(0);
}
