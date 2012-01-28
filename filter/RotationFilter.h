/*
 * RotationFilter.h
 *
 *  Created on: 3 Dec 2011
 *      Author: rob
 */

#ifndef ROTATIONFILTER_H_
#define ROTATIONFILTER_H_

#include "PointCloudFilter.h"

class RotationFilter: public PointCloudFilter {
private:
	Matrix4 transform;
public:
	enum rotation {
		ROTATE_XY,
		ROTATE_XZ,
		ROTATE_YZ
	};
	RotationFilter(rotation r, float theta);
	virtual ~RotationFilter();
	virtual void filterPointCloud(PointCloud & in);
};

#endif /* ROTATIONFILTER_H_ */
