/*
 * XZRotationFilter.cpp
 *
 *  Created on: 1 Nov 2011
 *      Author: rob
 */

#include "XZRotationFilter.h"
#include "MatrixFilter.h"

XZRotationFilter::XZRotationFilter(float theta)
{
	Matrix4 r;
	//Rotation of theta in XZ plane
	r << cos(theta), 0.0f, -sin(theta), 0.0f,
		 0.0f, 		 1.0f,  0.0f, 		0.0f,
		 sin(theta), 0.0f,  cos(theta), 0.0f,
		 0.0f,       0.0f,  0.0f, 		1.0f;
	transform = r;
}

XZRotationFilter::~XZRotationFilter() {
	// TODO Auto-generated destructor stub
}

void XZRotationFilter::filterPointCloud(PointCloud & in)
{
	MatrixFilter f(transform);
	f.filterPointCloud(in);
}


