#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<errno.h>


#define MAX 512
unsigned char bufg[MAX]={0x00};
unsigned char bufb[MAX]={0x00};

int fdg,fdb;


void append(unsigned char buf[]){
	int len;
	len = strlen(buf);
	buf[len++] = 0xd;
	buf[len] = 0xa;
}

int serial_port_init(unsigned char *dev)
{
	if(dev == NULL)
		return -1;
	int serial_port = open(dev, O_RDWR);

	// Create new termios struct, we call it 'tty' for convention
	struct termios tty;

	// Read in existing settings, and handle any error
	if(tcgetattr(serial_port, &tty) != 0) {
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
		return 1;
	}

	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
	tty.c_cflag |= CS8; // 8 bits per byte (most common)
	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
	// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

	tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 9600
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	// Save tty settings, also checking for error
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		return 1;
	}

	return serial_port;
}


int main(void){

	fdg=serial_port_init("/dev/ttyUSB0");
	fdb=serial_port_init("/dev/ttyUSB1");

	//while(1){
		if(fdg<0){

			printf("Failed to open GSM\n");
		}
		else if(fdb<0){
			printf("Failed to open BT\n");
		}
		else{
			unsigned char ph[MAX];
			printf("enter phone number\n");
			scanf("%s",ph);
			strcat(bufg,"at+cmgs=");
			strcat(bufg,"\"");
			strcat(bufg,ph);
			strcat(bufg,"\"");
			append(bufg);
			printf("AT command: %s \n", bufg);
			sleep(2);
			read(fdb,bufb,sizeof(bufb));
			printf("from bluetooth: %s\n",bufb);
			sleep(2);
			int len = strlen(bufb);
			bufb[len++]=0x1a;
			write(fdg, bufg,sizeof(bufg));
			sleep(5);
			write(fdg,bufb,sizeof(bufb));
			sleep(20);
			memset(bufg,0x00,MAX);
			memset(bufb,0x00,MAX);
		}
	//}
	return 0;
}


