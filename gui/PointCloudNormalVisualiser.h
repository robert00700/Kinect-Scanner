/*
 * PointCloudNormalVisualiser.h
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#ifndef POINTCLOUDNORMALVISUALISER_H_
#define POINTCLOUDNORMALVISUALISER_H_

#include "Visualiser.h"

#include <boost/thread/thread.hpp>
#include <pcl/visualization/point_cloud_handlers.h>
#include <pcl/visualization/pcl_visualizer.h>

class PointCloudNormalVisualiser : public Visualiser<PointCloud> {
protected:
	PointCloudNormals::Ptr normals;
	void drawObject();
public:
	void setNormals(PointCloudNormals & norm) {
		objectMutex.lock();
		normals.reset(new PointCloudNormals(norm));
		objectMutex.unlock();
	}
	PointCloudNormalVisualiser(std::string name="Visualiser") : Visualiser<PointCloud>(name) {}
	PointCloudNormalVisualiser(PointCloud in, std::string name="Visualiser") : Visualiser<PointCloud>(in, name) {}
};
#endif /* POINTCLOUDNORMALVISUALISER_H_ */
