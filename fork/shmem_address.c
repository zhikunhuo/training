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
        }

        printf("Child: Share memory addess :0x%x\n", (unsigned long)shm_addr);

        /* delet memory map*/
        if ((shmdt(shm_addr)) < 0)
        {
            perror("Shmdt");
            exit(1);
        } else {
            printf("Child: Dettach share memory\n");
        }


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
        }

        printf("Father process share address 0x%x\n",(unsigned long)shm_addr);

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
