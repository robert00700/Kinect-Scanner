/*
 * PointCloudVisualiser.cpp
 *
 *  Created on: 24 Oct 2011
 *      Author: rob
 */

#include "PointCloudVisualiser.h"

void PointCloudVisualiser::drawObject() {
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> handler (object);
	if(!firstPass) {
		visualiser->updatePointCloud(object, handler, "OpenNICloud");
	}
	else {
		firstPass = false;
		visualiser->addPointCloud(object, handler, "OpenNICloud");
		visualiser->resetCameraViewpoint ("OpenNICloud");
	}
}

