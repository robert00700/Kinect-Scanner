/*
 * PointCloudVisualiser.h
 *
 *  Created on: 24 Oct 2011
 *      Author: rob
 */

#ifndef POINTCLOUDVISUALISER_H_
#define POINTCLOUDVISUALISER_H_

#include "ScanTypes.h"
#include "gui/Visualiser.h"
#include <boost/thread/thread.hpp>
#include <pcl/visualization/point_cloud_handlers.h>
#include <pcl/visualization/pcl_visualizer.h>

class PointCloudVisualiser : public Visualiser<PointCloud> {
protected:
	void drawObject();
public:
	PointCloudVisualiser(std::string name="Visualiser") : Visualiser<PointCloud>(name) {}
	PointCloudVisualiser(PointCloud& in, std::string name="Visualiser") : Visualiser<PointCloud>(in, name) {}
};

#endif /* POINTCLOUDVISUALISER_H_ */
