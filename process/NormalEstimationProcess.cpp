/*
 * NormalEstimationProcess.cpp
 *
 *  Created on: 23 Jan 2012
 *      Author: rob
 */

#include "NormalEstimationProcess.h"

NormalEstimationProcess::NormalEstimationProcess(float radius) {
	//normalEstimator.setRadiusSearch(radius);
}

void NormalEstimationProcess::processPointCloud(const PointCloud& in) {
	//pcl::search::KdTree<XYZRGB>::Ptr search (new pcl::search::KdTree<XYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>(in));
	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB> ());

	normalEstimator.setKSearch(80);

	normalEstimator.setInputCloud(cloud);
	normalEstimator.setSearchMethod(tree);
	normalEstimator.compute(normals);

	ready = true;
}

NormalEstimationProcess::~NormalEstimationProcess() {
	// TODO Auto-generated destructor stub
}

