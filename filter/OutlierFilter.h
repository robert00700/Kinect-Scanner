/*
 * OutlierFilter.h
 *
 *  Created on: 23 Jan 2012
 *      Author: rob
 */

#ifndef OUTLIERFILTER_H_
#define OUTLIERFILTER_H_

#include "PointCloudFilter.h"
#include <pcl/filters/statistical_outlier_removal.h>

#define K_POINTS 50
#define SIGMA 1.0f

class OutlierFilter: public PointCloudFilter {
public:
	pcl::StatisticalOutlierRemoval<XYZRGB> sor;
public:
	OutlierFilter(int points = K_POINTS, float sigma = SIGMA);
	virtual void filterPointCloud(PointCloud & in);
	virtual ~OutlierFilter();
};

#endif /* OUTLIERFILTER_H_ */
