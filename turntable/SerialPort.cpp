/*
 * SerialPort.cpp
 *
 *	A hilariously hideous hack for serial communications... it does the job!
 *
 *  Created on: 6 Jan 2012
 *      Author: rob
 */

#include "SerialPort.h"

SerialPort::SerialPort() {
	system("stty -F /dev/ttyUSB0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
	//echo -n
}

void SerialPort::send(std::string data) {
	std::stringstream s;
	ss << "echo -n " << data;
	system(ss.str().c_str());
}

SerialPort::~SerialPort() {

}

