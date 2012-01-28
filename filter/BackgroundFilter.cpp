/*
 * BackgroundFilter.cpp
 *
 *  Created on: 5 Dec 2011
 *      Author: rob
 */

#include "BackgroundFilter.h"

BackgroundFilter::BackgroundFilter(float d) {
	depth = d;
}

BackgroundFilter::~BackgroundFilter() {
	// TODO Auto-generated destructor stub
}

bool BackgroundFilter::filterPoint(XYZRGB & in) {
	return (in.z < depth);
}
