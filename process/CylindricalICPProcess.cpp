/*
 * CylindricalICPProcess.cpp
 *
 *  Created on: 25 Jan 2012
 *      Author: rob
 */

#include "CylindricalICPProcess.h"

#include "filter/XZRotationFilter.h"

int CylindricalICPProcess::getClosestPointIndex(XYZRGB in) {
	return tree->searchClosestIndex(in, angleCoefficient);
}

void CylindricalICPProcess::fuseModel(const PointCloud& in) {
	PointCloud cpy(in);
	XZRotationFilter f(theta);
	f.filterPointCloud(cpy);
	PointCloud::iterator it = cpy.begin();
	while(it != cpy.end()) {
		model.push_back(*it);
		it++;
	}
	setModel(model);
}

float CylindricalICPProcess::getNewTheta(const PointCloud& c) {
	log("GETTING NEW THETA");

	//Take a mutable copy
	PointCloud input = PointCloud(c);

	//Firstly rotate by the current rotation
	XZRotationFilter rot(theta);
	rot.filterPointCloud(input);

	float thetaAccumulator = 0.0f;
	int countAccumulator = 0;

	//Iterate through every point
	PointCloud::iterator it = input.begin();
	while(it != input.end()) {
		//Get the closest point on the base model
		XYZRGB current = *it;

		int closestIndex = getClosestPointIndex(current);

		//If not nothing found
		if(closestIndex != -1) {
			//Make some cylindrical coord points
			CoctreePoint modelPoint(model[closestIndex]);
			CoctreePoint thisPoint(current);

			//Get a delta theta
			float dtheta = thisPoint.theta - modelPoint.theta;
			if(dtheta > PI) dtheta = dtheta - TWO_PI;
			if(dtheta < -PI) dtheta = dtheta + TWO_PI;

			//Increment accumulators
			thetaAccumulator += dtheta;
			countAccumulator++;

		}
		if(it != input.end()) it++;
		if(it != input.end()) it++;
		if(it != input.end()) it++;
		if(it != input.end()) it++;
		if(it != input.end()) it++;
		if(it != input.end()) it++;
				if(it != input.end()) it++;
				if(it != input.end()) it++;
				if(it != input.end()) it++;
				if(it != input.end()) it++;
				if(it != input.end()) it++;
						if(it != input.end()) it++;
						if(it != input.end()) it++;
						if(it != input.end()) it++;
						if(it != input.end()) it++;
	}

	//Now we work out the average drift
	float averageTheta = thetaAccumulator / (float)countAccumulator;
	theta += averageTheta;
}

void CylindricalICPProcess::processPointCloud(const PointCloud& in) {
	getNewTheta(in);
}

CylindricalICPProcess::CylindricalICPProcess(double bias, float r) {
	angleCoefficient = bias;
	maxTheta = r;
}

CylindricalICPProcess::~CylindricalICPProcess() {
	// TODO Auto-generated destructor stub
}

