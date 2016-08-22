#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    pid_t pid;
    int ret;


    if((pid= fork()) <0)
    {
        printf("Fork error\n");
	exit(1);
    }

    if (0 == pid)
    {

        printf("Child process is %d\n", getpid());
	raise(SIGSTOP);
	exit(0);
    } else 
    {
        sleep(1);
        if ((waitpid(pid, NULL, WNOHANG)) == 0)
	{

	    if (kill(pid, SIGKILL) == 0)
	    {
	        printf("Parent kill %d\n", pid);
	    }
	 }
	 waitpid(pid,NULL, 0);
	 exit(0);
     }
}
