#pragma once
#include <progbase/net.h>
#include <string>
#define BUFFER_LEN 1024

class Controller{
private:
	TcpClient * client;
	IpAddress * serverAddress;
	NetMessage * message;
public:
	Controller();
	~Controller();

	bool connect();
	bool * getInput ();
	void turnOnLed(int num);
	void turnOffLed(int num);
};
