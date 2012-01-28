/*
 * OutlierFilter.cpp
 *
 *  Created on: 23 Jan 2012
 *      Author: rob
 */

#include "OutlierFilter.h"

OutlierFilter::OutlierFilter(int k, float sigma) {
	sor.setMeanK(k);
	sor.setStddevMulThresh(sigma);
}

void OutlierFilter::filterPointCloud(PointCloud & in) {
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>(in));
	sor.setInputCloud(cloud);
	sor.filter(in);
}

OutlierFilter::~OutlierFilter() {
	// TODO Auto-generated destructor stub
}

