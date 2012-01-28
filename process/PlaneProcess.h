/*
 * PlaneProcess.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef PLANEPROCESS_H_
#define PLANEPROCESS_H_

#include "PointCloudProcess.h"

class PlaneProcess: public PointCloudProcess {
private:
	Vector position;
	float distance;
	Vector normal;
public:
	PlaneProcess();
	PlaneProcess(Vector _position, float _distance);
	virtual ~PlaneProcess();
	virtual void processPointCloud(const PointCloud & in);
	Vector getNormal() {
		if(isReady()) {
			return normal;
		}
		else {
			throw std::exception();
		}
	}
};

#endif /* PLANEPROCESS_H_ */
