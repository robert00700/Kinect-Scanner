/*
 * AverageProcess.cpp
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#include "AverageProcess.h"
#include <math.h>

AverageProcess::AverageProcess() {
	// TODO Auto-generated constructor stub

}

AverageProcess::~AverageProcess() {
	// TODO Auto-generated destructor stub
}

void AverageProcess::processPointCloud(const PointCloud & in)
{
	PointCloud::const_iterator it = in.begin();
	Vector calcAvg;
	int n = 0;
	float z;
	while(it != in.end()) {
		if(!isnan(it->x) && !isnan(it->y) && !isnan(it->z)) {
			float zs = it->z * it->z;
			calcAvg += Vector(it->x * zs, it->y * zs, it->z * zs);
			n++;
			z += zs;
		}
		it++;
	}
	average =  calcAvg / z;
	ready = true;
}


