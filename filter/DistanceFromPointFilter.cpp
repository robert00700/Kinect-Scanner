/*
 * DistanceFromPointFilter.cpp
 *
 *  Created on: 22 Jan 2012
 *      Author: rob
 */

#include "DistanceFromPointFilter.h"

DistanceFromPointFilter::DistanceFromPointFilter(Vector p, float d) {
	position = p;
	distance = d;
}

bool DistanceFromPointFilter::filterPoint(XYZRGB & in) {
	Vector test(in.x, in.y, in.z);
	return test.dist(position) <= distance;
}

DistanceFromPointFilter::~DistanceFromPointFilter() {
	// TODO Auto-generated destructor stub
}

