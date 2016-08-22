#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


#define BUFFSIZE 1024

int main()
{
    FILE *fp;
    char *cmd ="ps -ef";
    char buff[BUFFSIZE] ={0};

    if ((fp = popen(cmd, "r")) == NULL)
    {
        printf("Popen error\n");
	exit(1);
    }


    while((fgets(buff, BUFFSIZE, fp)) != NULL)
    {
        printf("%s", buff);
    }

    pclose(fp);
    exit(0);

}
