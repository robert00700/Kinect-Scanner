/*
 * CylindricalICPProcess.h
 *
 *  Created on: 25 Jan 2012
 *      Author: rob
 */

#ifndef CYLINDRICALICPPROCESS_H_
#define CYLINDRICALICPPROCESS_H_

#include "PointCloudProcess.h"
#include "ScanTypes.h"
#include "coctree/Coctree.h"

#define DEFAULT_BIAS 0.1
#define DEFAULT_MAX_THETA 0.06

class CylindricalICPProcess: public PointCloudProcess {
private:
	bool empty;
	float theta;
	float maxTheta;

	double angleCoefficient;

	PointCloud model;
	Coctree * tree;

	int getClosestPointIndex(XYZRGB in);
	float getNewTheta(const PointCloud& c);

public:
	CylindricalICPProcess(double m = DEFAULT_BIAS, float r = DEFAULT_MAX_THETA);
	virtual ~CylindricalICPProcess();
	virtual void processPointCloud(const PointCloud & in);

	float getTheta() {
		return theta;
	}
	void overrideTheta(float t) {
		theta = t;
	}
	PointCloud & getModel() {
		return model;
	}

	void fuseModel(const PointCloud & in);
	void setModel(PointCloud & in) {
		model = PointCloud(in);
		PointCloud::ConstPtr * ptr = new PointCloud::ConstPtr();
		ptr->reset(&model);
		delete tree;
		tree = new Coctree(0.35f, 0.5f, model);
	}
};

#endif /* CYLINDRICALICPPROCESS_H_ */
