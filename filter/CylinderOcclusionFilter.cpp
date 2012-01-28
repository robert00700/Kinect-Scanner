/*
 * CylinderOcclusionFilter.cpp
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#include "CylinderOcclusionFilter.h"

CylinderOcclusionFilter::CylinderOcclusionFilter() {
	// TODO Auto-generated constructor stub

}

CylinderOcclusionFilter::CylinderOcclusionFilter(Vector _position, Vector _normal, float _height, float _radius)
{
	position = _position;
	normal = _normal;
	height = _height;
	radius = _radius;
}

bool CylinderOcclusionFilter::filterPoint(XYZRGB & in)
{
	Vector3 currentPosition(in.x, in.y, in.z);
	//Map from world to cylinder relative coordinates
	currentPosition -= position;

	//Magnitude of cylinder bottom to this point
	float totMag = currentPosition.mag();

	//Magnitude of the point parallel to the cylinder
	float upMag = currentPosition * normal;

	//Magnitude perpendicular (radial)
	float radialMag = sqrt(totMag * totMag - upMag * upMag);

	//Work out if inside cylinder
	return (radialMag <= radius &&
		upMag >= 0.05f &&
		upMag <= height);

}

CylinderOcclusionFilter::~CylinderOcclusionFilter() {
	// TODO Auto-generated destructor stub
}
