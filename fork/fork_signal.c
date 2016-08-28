#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_func(int sign_no)
{

    if(sign_no == SIGINT)
    {
        printf("I have got SIGINT\n");
    } else if ( sign_no == SIGQUIT)
    {
        printf("I have got SIGQUIT\n");
    }

}
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
        signal(SIGINT, my_func);
        signal(SIGQUIT, my_func);
        while(1)
        {
         //   printf("loop \n");
        }
    } else
    {

        sleep(1);
        printf("Father process id is %d\n", getpid());
        printf("Send SIGINT signal to %d\n", result);
        kill(result, SIGINT);
        printf("Send SIGQUIT signal to %d\n", result);
        kill(result, SIGQUIT);
        printf("Send SIGKILL signal to %d\n", result);
        kill(result, SIGKILL);
    }

    return result;
}
