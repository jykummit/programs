#include <stdio.h>
#include <string.h>

#include <fcntl.h> 
#include <errno.h> 
#include <termios.h> 
#include <unistd.h> 


#define SIZE 1024
int len;
unsigned char buf[SIZE]=  {0x00};
int fd;


void appendcrlf(unsigned char* );

/*
struct msg_event {
	unsigned char no[14];
	unsigned char msg_id[2];
}; 

void send_sms(unsigned char *buf, unsigned char *ph)
{
	//frame at+cmgs   write(atcmgs="9492709581")
	strcat(buf,ph);
	appendcrlf(buf);
	write(fd,buf,sizeof(buf));


	char msg[] = "Hello";
	int len = strlen(msg);
	msg[len++] = 0x1a;
	//printf("%s\n",msg);
	write(fd,msg,sizeof(msg));
	sleep(1);
	
}
*/
void appendcrlf( unsigned char *buf)
{
	int len;
	len = strlen(buf);
	buf[len++] = 0xd;
	buf[len] = 0xa;
}
unsigned int get_msg_id(char *buf1, int len)
{
	int i=2;
	unsigned char read_sms[50];
	char a,b;
	unsigned char *buf = buf1;

	//+CMTI: 'SM',1
	//0x2b 0x43 0x4d 0x54 0x49 0x3a 0x20 0x22 0x53 0x4d 0x22 0x2c 
	if(buf[i++]==0x2b){
		if(buf[i++]==0x43){
			if(buf[i++]==0x4d){
				strcpy(read_sms,buf);
				a = buf1[15];
				b = buf1[16];
				strcat(read_sms,"at+cmgr=");
				strcat(read_sms,a);
				strcat(read_sms,b);
				appendcrlf(read_sms);
				printf("final: %s\n",read_sms);
				write(fd,read_sms,sizeof(read_sms));
				return 1;
			}
		}
	}
	else{
		return -1;
	}

	
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
void main(void)
{
	fd = serial_port_init("/dev/ttyUSB0");
	while(1)
	{
		read(fd, buf, SIZE);
		len = strlen(buf);
		printf("len: %d of buf %s\n",len,buf);
		sleep(3);
		//printf("%s: \n",buf);
		int res = get_msg_id((void *)buf, len);
		memset(buf, 0x00, SIZE);
	/*
		strcat(buf,"at+cmgs=");
		unsigned char ph[] = {0x22,0x39,0x31,0x37,0x37,0x39,0x37,0x36,0x32,0x32,0x30,0x22};
		send_sms(buf,ph);
		sleep(1);	
		read(fd, buf, SIZE);
		//len = strlen(buf);
		//printf("len: %d\n",len);
		printf("%s: \n",buf);
		memset(buf, 0x00,SIZE);
*/
	}
}

