#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


int main(){
	int fd = open("/dev/ttyUSB1",O_RDWR);
	char buf[512];
	if(read(fd,buf,sizeof(buf))!=0){
		printf("%s\n",buf);
	}
	else{
		printf("failed\n");
	}
	
	return 0;
}


