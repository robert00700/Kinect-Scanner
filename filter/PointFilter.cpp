/*
 * PointFilter.cpp
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#include "PointFilter.h"
#include <math.h>

PointFilter::PointFilter() {
	// TODO Auto-generated constructor stub
}

PointFilter::~PointFilter() {
	// TODO Auto-generated destructor stub
}

void PointFilter::filterPointCloud(PointCloud & in) {
	PointCloud copy(in);
	in.clear();
	PointCloud::iterator it = copy.begin();
	while(it != copy.end()) {
		if(filterPoint(*it) && !isnan(it->x) && !isnan(it->y) && !isnan(it->z)) {
			in.push_back(*it);
		}
		it++;
	}
}
