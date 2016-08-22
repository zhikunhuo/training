#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t result;

    /* create new process */
    result = fork();
    if (-1 == result)
    {
        printf("Fork error\n");
    } else if ( result ==0 ) /*children process */
    {
        printf("Child process id is %d\n", getpid());
    } else
    {
        printf("Father process id is %d\n", getpid());
    }

    return result;
}
