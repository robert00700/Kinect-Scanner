/*
 * AverageProcess.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef AVERAGEPROCESS_H_
#define AVERAGEPROCESS_H_

#include "PointCloudProcess.h"

class AverageProcess: public PointCloudProcess {
private:
	Vector average;
public:
	AverageProcess();
	virtual ~AverageProcess();
	virtual void processPointCloud(const PointCloud & in);
	Vector getAverage() {
		if(isReady()) {
			return average;
		}
		else {
			throw std::exception();
		}
	}
};

#endif /* AVERAGEPROCESS_H_ */
