#pragma once
#include <string>
#include <thread>
#include <mutex>

class Controller{
private:
	int fd;
	bool connected;
	std::thread * fetch;
	std::mutex m;
	bool values[4];
	bool updatable;
	void send(char * msg, int size);


	int set_interface_attribs (int speed, int parity);
	void fetchValues();

public:
	Controller();
	~Controller();

	bool isConnected();
	bool * getInput ();
	void turnOnLed(int num);
	void turnOffLed(int num);
};