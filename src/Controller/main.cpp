#include <iostream>
#include "include/Controller.h"

int main(void){

	Controller * controller = new Controller();
	controller->connect();

	while(1){
		int com;
		std::cin >> com;
		switch(com){
			case 0:{
				int led;
				std::cin >> led;
				controller->turnOffLed(led);
			}break;
			case 1:{
				int led;
				std::cin >> led;
				controller->turnOnLed(led);
			}break;
			case 2:{
				int con;
				std::cin >> con;
				int distance = controller->distanceFrom(con);
				std::cout << distance << std::endl;
			}break;
		}
	}

	delete controller;
	return 0;
}