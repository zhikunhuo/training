#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_func(int sign_no)
{
    if(sign_no == SIGINT)
    {
        printf("I have get SIGINT\n");
    }
    else if (sign_no == SIGQUIT)
    {
        printf("I have get SIGQUIT\n");
    }

}

int main()
{
    sigset_t set, pendset;

    /* init set */
    if (sigemptyset(&set) < 0)
    {
        perror("sigemptyset");
        exit(1);
    }

    /* add SIGQUIT signal into set */
    if(sigaddset(&set, SIGQUIT) < 0)
    {
        perror("sigaddset");
        exit(1);
    }

    /* add SIGINT signal into set*/
    if (sigaddset(&set, SIGINT) < 0)
    {
        perror("sigaddset");
        exit(1);
    }

    /* set signal mask */
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0)
    {
        perror("sigprocmask");
        exit(1);
    }

    if(sigprocmask(0,NULL, &pendset) < 0)
    {
        perror("sigprocmask");
        exit(1);
    }


    if(sigismember(&pendset, SIGINT))
    {
        printf("Block SIGINT\n");
    }


    if (sigismember(&pendset, SIGQUIT))
    {
        printf("Block SIGQUIT\n");
    }

}
     
