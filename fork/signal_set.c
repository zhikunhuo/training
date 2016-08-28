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
    struct sigaction action1, action2;

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

    /*set SIGINT handler */
    if(sigismember(&set, SIGINT))
    {
        sigemptyset(&action1.sa_mask);
        action1.sa_handler = my_func;
        action1.sa_flags = 0;
        sigaction(SIGINT, &action1, NULL);
    }


    /* set SIGQUIT handler */
    if(sigismember(&set, SIGQUIT))
    {

       sigemptyset(&action2.sa_mask);
       action2.sa_handler = my_func;
       action2.sa_flags = 0;
       sigaction(SIGQUIT, &action2,NULL);
    }


    /* set signal mask */
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0)
    {
        perror("sigprocmask");
        exit(1);
    }
    else 
    {
        printf("Signal set was blocked, Press any key!");
        getchar();
    }

    if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0)
    {
        perror("Sigprocmask");
        exit(1);
    }
    else
    {
        printf("Signal set is in unblock state\n");
    }


    while(1);
    exit(0);
}
