/*
 * NormalEstimationProcess.h
 *
 *  Created on: 23 Jan 2012
 *      Author: rob
 */

#ifndef NORMALESTIMATIONPROCESS_H_
#define NORMALESTIMATIONPROCESS_H_

#include "PointCloudProcess.h"
#include <pcl/features/normal_3d_omp.h>

#define DEFAULT_RADIUS 0.05f

class NormalEstimationProcess: public PointCloudProcess {
private:
	PointCloudNormals normals;
	pcl::NormalEstimationOMP<XYZRGB, pcl::Normal> normalEstimator;
public:
	NormalEstimationProcess(float radius = DEFAULT_RADIUS);
	PointCloudNormals& getNormals() {
		return normals;
	}
	virtual void processPointCloud(const PointCloud& in);
	virtual ~NormalEstimationProcess();
};

#endif /* NORMALESTIMATIONPROCESS_H_ */
