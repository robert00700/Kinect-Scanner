/*
 * PointCloudFilter.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef POINTCLOUDFILTER_H_
#define POINTCLOUDFILTER_H_

#include "../ScanTypes.h"

class PointCloudFilter {
public:
	PointCloudFilter();
	virtual ~PointCloudFilter();
	virtual void filterPointCloud(PointCloud & in) = 0;
};

#endif /* POINTCLOUDFILTER_H_ */
