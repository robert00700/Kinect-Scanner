/*
 * PointCloudNormalVisualiser.cpp
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#include "PointCloudNormalVisualiser.h"

void PointCloudNormalVisualiser::drawObject() {
	pcl::visualization::PointCloudColorHandlerRGBField<XYZRGB> handler (object);
	if(!firstPass) {
		visualiser->updatePointCloud(object, handler, "OpenNICloud");

		PointCloud::Ptr ptr1(object);
		PointCloudNormals::Ptr ptr2(normals);
		visualiser->removePolygonMesh("Lad");
		visualiser->addPointCloudNormals<XYZRGB, pcl::Normal>(ptr1, ptr2, 100, 0.02, "Lad");
	}
	else {
		firstPass = false;
		visualiser->addPointCloud(object, handler, "OpenNICloud");
		visualiser->resetCameraViewpoint ("OpenNICloud");
	}
}
