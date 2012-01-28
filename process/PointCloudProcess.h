/*
 * PointCloudProcess.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef POINTCLOUDPROCESS_H_
#define POINTCLOUDPROCESS_H_

#include "../ScanTypes.h"

class PointCloudProcess {
protected:
	bool ready;
public:
	PointCloudProcess() {
		ready = false;
	}
	virtual ~PointCloudProcess();
	virtual void processPointCloud(const PointCloud & in) = 0;
	virtual bool isReady() {
		return ready;
	}
};

#endif /* POINTCLOUDPROCESS_H_ */
