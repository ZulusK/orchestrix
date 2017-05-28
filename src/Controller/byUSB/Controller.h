#pragma once
#include <string>

class Controller{
private:
	int fd;
	bool connected;

	int set_interface_attribs (int speed, int parity);

public:
	Controller();

	bool isConnected();
	bool * getInput ();
	void turnOnLed(int num);
	void turnOffLed(int num);
};
