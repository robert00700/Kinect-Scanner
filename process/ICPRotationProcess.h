/*
 * ICPRotationProcess.h
 *
 *  Created on: 30 Oct 2011
 *      Author: rob
 */

#ifndef ICPROTATIONPROCESS_H_
#define ICPROTATIONPROCESS_H_

#include "PointCloudProcess.h"
#include "ScanTypes.h"
#include <pcl/kdtree/kdtree_flann.h>

#define DEFAULT_MAX 0.1f //30cm

class ICPRotationProcess : PointCloudProcess {
private:
	pcl::KdTreeFLANN<XYZRGB> tree;
	PointCloud model;
	PointCloudNormals modelNormals;
	bool empty;
	float theta;

	float max; //maximum distance from closest point before we stop caring
	Vector getClosestPoint(Vector in);
	int getClosestPointIndex(Vector in);
	float getNewTheta(const PointCloud& c);
	void recalculateModelNormals();
public:
	//void addCloud(PointCloud& c);
	float getTheta() {
		return theta;
	}
	void overrideTheta(float t) {
		theta = t;
	}
	PointCloud & getModel() {
		return model;
	}
	PointCloudNormals & getModelNormals() {
		return modelNormals;
	}
	void fuseModel(const PointCloud & in);
	void setModel(PointCloud & in) {
		model = PointCloud(in);
		PointCloud::ConstPtr * ptr = new PointCloud::ConstPtr();
		ptr->reset(&model);
		tree.setInputCloud(*ptr);
		recalculateModelNormals();
	}
	ICPRotationProcess(float m = DEFAULT_MAX);
	virtual ~ICPRotationProcess();
	virtual void processPointCloud(const PointCloud & in);
};

#endif /* ICPROTATIONPROCESS_H_ */
