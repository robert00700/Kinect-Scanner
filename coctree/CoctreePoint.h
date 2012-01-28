/*
 * CoctreePoint.h
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#ifndef COCTREEPOINT_H_
#define COCTREEPOINT_H_
#include "ScanTypes.h"
#include "math.h"

#define log(X) std::cout << X << std::endl;

struct CoctreePoint {
public:
	double theta;
	double radius;
	double height;
	int index;
	CoctreePoint(double _theta=0.0, double _r=0.0, double _h=0.0, int _index=0) {
		theta = _theta;
		radius = _r;
		height = _h;
		index = _index;
	}
	template <class T>
	CoctreePoint(T in, int _index=0) {
		theta = atan2(in.x, in.z) + TO_RAD * 180.0f;
		radius = sqrt(in.x * in.x + in.z * in.z);
		height = in.y;
		index = _index;
	}
};

#endif /* COCTREEPOINT_H_ */
