/*
 * TurntableProcess.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef TURNTABLEPROCESS_H_
#define TURNTABLEPROCESS_H_

#include "PointCloudProcess.h"

class TurntableProcess: public PointCloudProcess {
private:
	const static float DEFAULT_RADIUS = 0.1f;
	const static float DEFAULT_ACCURACY = 25.0f;

	float distance;
	Vector color;
	float accuracy;

	Vector up;
	Vector fwd;
	Vector side;
	Vector position;
public:
	TurntableProcess(float _distance = DEFAULT_RADIUS, Vector _color = Vector(202.0f, 26.0f, 161.0f), float _accuracy = DEFAULT_ACCURACY);
	virtual ~TurntableProcess();
	virtual void processPointCloud(const PointCloud & in);
	void setColor(Vector c) {
		color = c;
	}
	Vector getPosition() {
		if(isReady()) {
			return position;
		}
		else {
			throw std::exception();
		}
	}
	Vector getUp() {
		if(isReady()) {
			return up;
		}
		else {
			throw std::exception();
		}
	}
	Vector getFwd() {
		if(isReady()) {
			return fwd;
		}
		else {
			throw std::exception();
		}
	}
	Vector getSide() {
		if(isReady()) {
			return side;
		}
		else {
			throw std::exception();
		}
	}
};

#endif /* TURNTABLEPROCESS_H_ */
