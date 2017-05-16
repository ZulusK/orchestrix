#pragma once
#include <progbase/net.h>
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
	int distanceFrom(int num);
	void turnOnLed(int num);
	void turnOffLed(int num);
};