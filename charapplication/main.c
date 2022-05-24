#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<uacess.h>


int main(){
	int fd,len;
	unsigned char *buff[1024];
	unsigned char *s="hi hello everyone";
	fd=open("/dev/Example_driver",O_RDWR);
	if(fd<0)
	{
		len=strlen[buff];
		printf("file not open");
		int ret=read(fd,buff,len);
		printf("%d",ret);
		close(fd);
	}
	return 0;
}

