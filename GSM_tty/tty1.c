// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int main() {
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  int i;
  int serial_port = open("/dev/ttyUSB0", O_RDWR);

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
  char read_buf [256];
  int num_bytes;

  while(1)
  {
  // Write to serial port
 // unsigned char msg[] = { 0x6d, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d ,0x1a,0xd, 0xa};
  unsigned char msg[] = {0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x00, 0xd, 0xa};
  unsigned char cmgf[] = {0x41, 0x54, 0x2b, 0x43, 0x4d, 0x47, 0x46, 0x3d, 0x31,0xd, 0xa};
  unsigned char cmgs[] = {0x41, 0x54, 0x2b, 0x43, 0x4d, 0x47, 0x53, 0x3d, 0x22, 0x39, 0x31, 0x37, 0x37, 0x39, 0x37, 0x36, 0x32, 0x32, 0x30, 0x22, 0xd, 0xa};

unsigned char call[]={0x41, 0x54, 0x2b, 0x43, 0x4d, 0x47, 0x53, 0x3d, 0x22, 0x37, 0x35, 0x36, 0x39, 0x33, 0x33, 0x37, 0x30, 0x36, 0x30, 0x22, 0x0a, 0xa, 0xd };


  write(serial_port, cmgf, sizeof(cmgf));
  num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
  printf("Received data: %s\n", read_buf);
  sleep(1);
  printf("\n");
  memset(&read_buf, '\0', sizeof(read_buf));

  write(serial_port, cmgs, sizeof(cmgs));
  num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
  printf("Received data: %s\n", read_buf);
  printf("\n");
  sleep(1);
  memset(&read_buf, '\0', sizeof(read_buf));
  
  write(serial_port, msg, sizeof(msg));
  num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
  printf("Received data: %s\n", read_buf);
  printf("\n");
  sleep(30);
  memset(&read_buf, '\0', sizeof(read_buf));

  write(serial_port, call, sizeof(read_buf));
  num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
   printf("Received data: %s\n", read_buf);
  printf("\n");
  sleep(1);
  memset(&read_buf, '\0', sizeof(read_buf));

  }
  close(serial_port);
  return 0; // success
};
