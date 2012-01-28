/*
 * XZRotationFilter.cpp
 *
 *  Created on: 1 Nov 2011
 *      Author: rob
 */

#include "RotationFilter.h"
#include "MatrixFilter.h"

RotationFilter::RotationFilter(rotation rot, float theta)
{
	Matrix4 r;
	switch(rot) {
	case ROTATE_XY:
		r << cos(theta), -sin(theta), 	0.0f,	0.0f,
			 sin(theta),  cos(theta), 	0.0f,	0.0f,
			 0.0f,		 	0.0f,	  	1.0f,	0.0f,
			 0.0f, 			0.0f,		0.0f, 	1.0f;
		break;
	case ROTATE_XZ:
		r << cos(theta), 0.0f, -sin(theta), 0.0f,
			 0.0f, 		 1.0f,  0.0f, 		0.0f,
			 sin(theta), 0.0f,  cos(theta), 0.0f,
			 0.0f,       0.0f,  0.0f, 		1.0f;
		break;
	case ROTATE_YZ:
		r << 1.0f, 0.0f, 		0.0f,	 	0.0f,
			 0.0f, cos(theta), -sin(theta),	0.0f,
			 0.0f, sin(theta),  cos(theta), 0.0f,
			 0.0f, 0.0f,  		0.0f, 		1.0f;
		break;
	}
	transform = r;
}

RotationFilter::~RotationFilter()
{
	// TODO Auto-generated destructor stub
}

void RotationFilter::filterPointCloud(PointCloud & in)
{
	MatrixFilter f(transform);
	f.filterPointCloud(in);
}


