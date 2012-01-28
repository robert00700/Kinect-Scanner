/*
 * DistanceFromPointFilter.h
 *
 *  Created on: 22 Jan 2012
 *      Author: rob
 */

#ifndef DISTANCEFROMPOINTFILTER_H_
#define DISTANCEFROMPOINTFILTER_H_

#include "PointFilter.h"
#define DEFAULT_POSITION Vector(0.0f,0.0f,0.0f)
#define DEFAULT_DISTANCE 0.5f

class DistanceFromPointFilter: public PointFilter {
private:
	float distance;
	Vector position;
public:
	DistanceFromPointFilter(Vector pos = DEFAULT_POSITION, float dist = DEFAULT_DISTANCE);
	virtual bool filterPoint(XYZRGB & in);
	virtual ~DistanceFromPointFilter();
};

#endif /* DISTANCEFROMPOINTFILTER_H_ */
