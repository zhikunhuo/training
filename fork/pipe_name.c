#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MYFIFO "myfifo"


#define MAX_DATA_LEN 128
#define DELAY_TIME 1

int main()
{

    pid_t pid;
    int pipe_fd[2];
    char buf[MAX_DATA_LEN] = {0};
    const char data[] ="Pipe Test Program";
    int real_read, real_write;
    int fd = 0;

   // memset((void *)buf, 0, sizeof(buf));
    if(access(MYFIFO, F_OK) == -1)
    {
        if ((mkfifo(MYFIFO, 0666) < 0) )
	{
            printf("Can not create fifo file\n");
	    exit(1);
	}
    }

    if((pid = fork()) == 0)
    {
        /* open write fifo */
	fd= open(MYFIFO,O_WRONLY);
	if ( fd == -1)
	{
	    printf("Open write file error\n");
	    exit(1);
	}

	if(write(fd, data, strlen(data)) > 0)
	{
	    printf("Write %s to FIFO\n", data);
	}

	close(fd);

	exit(0);
     } else if (pid > 0) 
     {
         /*close read fd*/
	 fd = open(MYFIFO, O_RDONLY);
	 if (fd == -1)
	 {
	     printf("Open fifo error\n");
	     exit(1);
	 }

         if(read(fd, buf, MAX_DATA_LEN) > 0)
	 {
	     printf("Read %s from FIFO\n", buf);
	 }

	 close(fd);

	 exit(0);
      }

      return 0;
}
