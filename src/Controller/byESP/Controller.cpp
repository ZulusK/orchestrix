#include "Controller.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

bool * Controller::getInput(){

	char messageStr[BUFFER_LEN];
	std::sprintf(messageStr, "0");

	NetMessage_setDataString(message, messageStr);

	if(!TcpClient_send(client, message)) return NULL;
	NetMessage_setDataString(message, "");
	while(strcmp(NetMessage_data(message), "") == 0) 
	if(!TcpClient_receive(client, message)) return NULL;

	std::cout << NetMessage_data(message) << std::endl;

	bool * values = new bool [4];
	std::string answer = std::string(NetMessage_data(message));
	for(int i = 0; i < 4; i++){
		values[i] = answer.at(i) == '0' ? false : true;
	}

	return values;
}

void Controller::turnOnLed(int num){
	if(num > 4 || num < 0) return;

	char messageStr[BUFFER_LEN];
	std::sprintf(messageStr, "1;%i;1", num);

	NetMessage_setDataString(message, messageStr);
	if(!TcpClient_send(client, message)) std::cout << "Not sent" << std::endl;
	NetMessage_setDataString(message, "");
}

void Controller::turnOffLed(int num){
	if(num > 4 || num < 0) return;

	char messageStr[BUFFER_LEN];
	std::sprintf(messageStr, "1;%i;0", num);

	NetMessage_setDataString(message, messageStr);
	if(!TcpClient_send(client, message)) std::cout << "Not sent" << std::endl;
	NetMessage_setDataString(message, "");
}
