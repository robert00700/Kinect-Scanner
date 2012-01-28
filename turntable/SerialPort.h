/*
 * SerialPort.h
 *
 *  Created on: 6 Jan 2012
 *      Author: rob
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

class SerialPort {
public:
	SerialPort();
	void send(std::string data);
	virtual ~SerialPort();
};

#endif /* SERIALPORT_H_ */
