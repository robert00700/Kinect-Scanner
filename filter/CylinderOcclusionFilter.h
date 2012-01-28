/*
 * CylinderOcclusionFilter.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef CYLINDEROCCLUSIONFILTER_H_
#define CYLINDEROCCLUSIONFILTER_H_

#include "PointFilter.h"

class CylinderOcclusionFilter: public PointFilter {
private:
	  Vector position;
	  Vector normal;
	  float height;
	  float radius;
public:
	CylinderOcclusionFilter();
	CylinderOcclusionFilter(Vector _position, Vector _normal, float _height, float _radius);
	virtual ~CylinderOcclusionFilter();
	virtual bool filterPoint(XYZRGB & in);

};

#endif /* CYLINDEROCCLUSIONFILTER_H_ */
