#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	int fd,len;
	char *s1 = "Hello World";
	char buff[1024];
	len = strlen(s1);
	fd = open("/dev/char_drv",O_RDWR);
	write(fd,s1,len);
	int ret = read(fd,buff,len);
	//printf("%d\n",ret);
	printf("%d\n",len);
	close(fd);
	return 0;
}


