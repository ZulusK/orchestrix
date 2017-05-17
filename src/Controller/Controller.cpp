#include "../include/Controller.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

Controller::Controller(){
	client = NULL;
	serverAddress = NULL;
	message = NULL;
}

bool Controller::connect(){
	if(client != NULL){
		TcpClient_close(client);
		delete message;
		delete serverAddress;
		delete client;
	}

	client = new TcpClient();
	client = TcpClient_init(client);

	serverAddress = new IpAddress();
	serverAddress = IpAddress_init(serverAddress, "192.168.0.1", 80);

	message = new NetMessage();
	char * buffer = new char[BUFFER_LEN];
	message = NetMessage_init(message, buffer, BUFFER_LEN);

	return TcpClient_connect(client, serverAddress);
}

Controller::~Controller(){
    TcpClient_close(client);
	delete message;
	delete serverAddress;
	delete client;
}

int Controller::distanceFrom(int num){
	if(num >= 4 || num < 0) return -1;

	char messageStr[BUFFER_LEN];
	std::sprintf(messageStr, "0;%i", num);

	NetMessage_setDataString(message, messageStr);

	if(!TcpClient_send(client, message)) return -1;
	if(!TcpClient_receive(client, message)) return -1;

	int dis = std::atoi(message->buffer);
	NetMessage_setDataString(message, "");

	return dis;
}

void Controller::turnOnLed(int num){
	if(num > 4 || num < 0) return;

	char messageStr[BUFFER_LEN];
	std::sprintf(messageStr, "1;%i;1", num);

	NetMessage_setDataString(message, messageStr);
	TcpClient_send(client, message);
	NetMessage_setDataString(message, "");
}

void Controller::turnOffLed(int num){
	if(num > 4 || num < 0) return;

	char messageStr[BUFFER_LEN];
	std::sprintf(messageStr, "1;%i;0", num);

	NetMessage_setDataString(message, messageStr);
	TcpClient_send(client, message);
	NetMessage_setDataString(message, "");
}