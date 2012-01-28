/*
 * StepperMotor.h

 *  Created on: 6 Jan 2012
 *      Author: rob
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#define SMALL_MOTOR_STEPS_PER_REVOLUTION 2048

class StepperMotor {
private:
	float theta; //current angle of rotation
	float stepsPerRevolution; //total number of 'steps' sent to the motor to make it do a full rotation
	boost::mutex mut;
	SerialPort sp;
public:
	StepperMotor(float _stepsPerRevolution = SMALL_MOTOR_STEPS_PER_REVOLUTION);
	float getTheta() {
		mut.lock();
		float currentTheta = theta;
		mut.unlock();
		return currentTheta;
	}
	void incrementTheta(float delta) {
		mut.lock();
		char steps = stepsPerRevolution * delta;
		std::string encode(steps, 1);
		sp.send(encode);
		//sleep the thread to keep things sharp
		boost::this_thread::sleep(boost::posix_time::milliseconds(200));
		mut.unlock();
	}
	virtual ~StepperMotor();
};

#endif /* STEPPERMOTOR_H_ */
