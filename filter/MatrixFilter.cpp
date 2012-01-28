/*
 * MatrixFilter.cpp
 *
 *  Created on: 31 Oct 2011
 *      Author: rob
 */

#include "MatrixFilter.h"

void MatrixFilter::filterPointCloud(PointCloud & in)
{
	PointCloud copy(in);
	in.clear();
	PointCloud::iterator it = copy.begin();
	while(it != copy.end()) {
		if(!isnan(it->x) && !isnan(it->y) && !isnan(it->z)) {
			XYZRGB p = *it;
			Vector4 four(p.x, p.y, p.z, 1.0f);
			four = transform * four;
			p.x = four(0) / four(3);
			p.y = four(1) / four(3);
			p.z = four(2) / four(3);
			in.push_back(p);
		}
		it++;
	}
}

MatrixFilter::MatrixFilter(Matrix4 & in)
{
	transform = in;
}

MatrixFilter::~MatrixFilter() {
	// TODO Auto-generated destructor stub
}
