#include "Controller.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>


Controller::Controller(){
	connected = true;
	fd = open ("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) connected = false;
	if(set_interface_attribs (B115200, 0) < 0) connected = false;  // set speed to 115,200 bps, 8n1 (no parity)

	turnOnLed(1);

	updatable=true;
	fetch = new std::thread(&Controller::fetchValues,this);
}

Controller::~Controller(){
	updatable = false;
	fetch->join();
	delete fetch;
}

int Controller::set_interface_attribs (int speed, int parity){
		struct termios tty;
		memset (&tty, 0, sizeof tty);
		if (tcgetattr (fd, &tty) != 0) return -1;

		cfsetospeed (&tty, speed);
		cfsetispeed (&tty, speed);

		tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
		// disable IGNBRK for mismatched speed tests; otherwise receive break
		// as \000 chars
		tty.c_iflag &= ~IGNBRK;         // disable break processing
		tty.c_lflag = 0;                // no signaling chars, no echo,
										// no canonical processing
		tty.c_oflag = 0;                // no remapping, no delays
		tty.c_cc[VMIN]  = 1;            // read blocks
		tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

		tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

		tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
										// enable reading
		tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
		tty.c_cflag |= parity;
		tty.c_cflag &= ~CSTOPB;
		tty.c_cflag &= ~CRTSCTS;

		if (tcsetattr (fd, TCSANOW, &tty) != 0) return -1;
		return 0;
}

bool Controller::isConnected(){
	return connected;
}
void Controller::fetchValues(){
	while(updatable){
		char message[] = "0";
	send(message,sizeof(message)/sizeof(message[0]));

		char answer[10];
		read(fd, answer, 10*sizeof(char));

		bool * newValues = new bool [4];
		for(int i = 0; i < 4; i++){
			newValues[i] = answer[i] == '0' ? false : true;
		}
		m.lock();
		for(int i = 0; i < 4; i++){
			values[i] = newValues[i];
		}
		m.unlock();
		std::cout << updatable << std::endl;

		delete newValues;
	}
}

bool * Controller::getInput(){

	bool * ret = new bool [4];
	m.lock();
	for(int i = 0; i < 4; i++){
		ret[i] = values[i];
        values[i]=false;
	}
	m.unlock();

	return ret;
}
void Controller::send(char * msg, int size){
	write(fd, msg, size*sizeof(msg[0]));
	usleep(size * 87);	
}
void Controller::turnOnLed(int num){

	char message[10];
	std::sprintf(message, "1;%i;1", num);

	send(message,sizeof(message)/sizeof(message[0]));
}

void Controller::turnOffLed(int num){
	if(num > 4 || num < 0) return;

	char message[10];
	std::sprintf(message, "1;%i;0", num);

	send(message,sizeof(message)/sizeof(message[0]));
}
