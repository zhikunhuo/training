#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_DATA_LEN 128
#define DELAY_TIME 1

int main()
{

    pid_t pid;
    int pipe_fd[2];
    char buf[MAX_DATA_LEN] = {0};
    const char data[] ="Pipe Test Program";
    int real_read, real_write;

   // memset((void *)buf, 0, sizeof(buf));

    if( pipe(pipe_fd) < 0)
    {
        printf("Pipe create error\n");
	exit(1);
    }

    if((pid = fork()) == 0)
    {
        /* clode write fd */
	close(pipe_fd[1]);
	sleep(DELAY_TIME *3);

	if ((real_read = read(pipe_fd[0], buf, MAX_DATA_LEN)) > 0)
	{
	    printf("Read data from pipe is %s\n", buf);
	}

	close(pipe_fd[0]);
	exit(0);
     } else if (pid > 0) 
     {
         /*close read fd*/
	 close(pipe_fd[0]);
	 sleep(DELAY_TIME);

	 if ((real_write = write(pipe_fd[1], data,  strlen(data))) != -1)
	 {
	     printf("Write to pipe is: %s\n", data);
	 }


	 close(pipe_fd[1]);
	 waitpid(pid, NULL, 0);
	 exit(0);
      }

      return 0;
}
