/*
 * ColorFilter.cpp
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#include "ColorFilter.h"

ColorFilter::ColorFilter() {
	// TODO Auto-generated constructor stub
}

ColorFilter::ColorFilter(Vector _color, float _accuracy) {
	color = _color;
	accuracy = _accuracy;
}

bool ColorFilter::filterColor(float r, float g, float b) {
	Vector test(r,g,b);
	return (color.dist(test) < accuracy);
}

ColorFilter::~ColorFilter() {
	// TODO Auto-generated destructor stub
}

bool ColorFilter::filterPoint(XYZRGB & in) {
	return filterColor(in.r, in.g, in.b);
}


