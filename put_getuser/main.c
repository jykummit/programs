#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>



int main(void){
	int fd;
	//char buff[50] = "Hello World to and fro Kernel to User";
	char *buff = "H";
	char kerndata[50];
	//int len = strlen(buff);
	fd = open("/dev/example_char_device",O_RDWR);
	if(fd < 0){
		perror(" ");
	}
	else{
		write(fd,buff,sizeof(char));
		printf("data from user %s\n",buff);

		read(fd,kerndata,sizeof(char));
		printf("data from kernel %s\n",kerndata);
	}
	close(fd);
	return 0;
}

