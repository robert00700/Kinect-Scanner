/*
 * ColorFilter.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef COLORFILTER_H_
#define COLORFILTER_H_

#include "PointFilter.h"

class ColorFilter: public PointFilter {
private:
	Vector 	color;
	float 	accuracy;
	bool filterColor(float r, float g, float b);
public:
	ColorFilter();
	ColorFilter(Vector _color, float _accuracy);
	virtual ~ColorFilter();
	virtual bool filterPoint(XYZRGB & in);
	void setColor(Vector _color) {
		color = _color;
	}
	Vector getColor() {
		return color;
	}
	void setAccuracy(float _accuracy) {
		accuracy = _accuracy;
	}
	float getAccuracy() {
		return accuracy;
	}
};

#endif /* COLORFILTER_H_ */
