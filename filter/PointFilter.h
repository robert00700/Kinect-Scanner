/*
 * PointFilter.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef POINTFILTER_H_
#define POINTFILTER_H_

#include "PointCloudFilter.h"

class PointFilter: public PointCloudFilter {
public:
	PointFilter();
	virtual ~PointFilter();
	virtual void filterPointCloud(PointCloud & in);
	virtual bool filterPoint(XYZRGB & in) = 0;
};

#endif /* POINTFILTER_H_ */
