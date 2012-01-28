/*
 * XZRotationFilter.h
 *
 *  Created on: 1 Nov 2011
 *      Author: rob
 */

#ifndef XZROTATIONFILTER_H_
#define XZROTATIONFILTER_H_

#include "PointCloudFilter.h"

class XZRotationFilter: public PointCloudFilter {
private:
	Matrix4 transform;
public:
	XZRotationFilter(float theta);
	virtual ~XZRotationFilter();
	virtual void filterPointCloud(PointCloud & in);
};

#endif /* XZROTATIONFILTER_H_ */
