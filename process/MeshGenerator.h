/*
 * MeshGenerator.h
 *
 *  Created on: 2 Dec 2011
 *      Author: rob
 */

#ifndef MESHGENERATOR_H_
#define MESHGENERATOR_H_

#include "PointCloudProcess.h"

class MeshGenerator: public PointCloudProcess {
private:
	PolyMesh::ConstPtr mesh;
public:
	MeshGenerator();
	virtual ~MeshGenerator();
	virtual void processPointCloud(const PointCloud & in);
	virtual PolyMesh::ConstPtr generateMesh(const PointCloud & in) = 0;
};

#endif /* MESHGENERATOR_H_ */
