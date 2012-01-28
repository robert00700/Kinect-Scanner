/*
 * TurntableCoordinateFilter.cpp
 *
 *  Created on: 24 Oct 2011
 *      Author: rob
 */

#include "TurntableCoordinateFilter.h"
#include "MatrixFilter.h"
#include <iostream>

TurntableCoordinateFilter::TurntableCoordinateFilter() {
	// TODO Auto-generated constructor stub
}

TurntableCoordinateFilter::~TurntableCoordinateFilter() {
	// TODO Auto-generated destructor stub
}

TurntableCoordinateFilter::TurntableCoordinateFilter(Vector position, Vector normal, Vector forward, Vector side)
{
	//Matrix to change coordinate system
	 Matrix4 o;
	 o << side.x, side.y, side.z, 0.0f,
	   normal.x, normal.y, normal.z, 0.0f,
	   forward.x, forward.y, forward.z, 0.0f,
	 0.0f,0.0f,0.0f,1.0f;

	 //Translation matrix to move turntable origin to origin
	 Matrix4 m;
	 m << 1.0f , 0.0f , 0.0f , -position.x
	   , 0.0f , 1.0f , 0.0f , -position.y
	   , 0.0f , 0.0f , 1.0f , -position.z
	   , 0.0f , 0.0f , 0.0f , 1.0f;

	 transform = o * m;

}

void TurntableCoordinateFilter::filterPointCloud(PointCloud & in)
{
	MatrixFilter f(transform);
	f.filterPointCloud(in);
}


