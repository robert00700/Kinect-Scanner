/*
 * TurntableCalibrationVisualiser.cpp
 *
 *  Created on: 25 Oct 2011
 *      Author: rob
 */

#include "TurntableCalibrationVisualiser.h"

TurntableCalibrationVisualiser::~TurntableCalibrationVisualiser() {
}

void TurntableCalibrationVisualiser::updateInfo(Vector _position, Vector _normal) {
	//cylinderMutex.lock();
	position = _position;
	normal = _normal;
	cylinderReady = true;
	//cylinderMutex.unlock();
}

void TurntableCalibrationVisualiser::postDraw() {
	if(cylinderReady) {
		 pcl::ModelCoefficients cylinder_coeff;
		 cylinder_coeff.values.resize (7);    // We need 7 values

		 Vector normNormal = normal.norm();
		 normNormal = normNormal * height;

		 //cylinderMutex.lock();
		 cylinder_coeff.values[0] = position.x;
		 cylinder_coeff.values[1] = position.y;
		 cylinder_coeff.values[2] = position.z;
		 cylinder_coeff.values[3] = normNormal.x;
		 cylinder_coeff.values[4] = normNormal.y;
		 cylinder_coeff.values[5] = normNormal.z;
		 cylinder_coeff.values[6] = radius;
		 //cylinderMutex.unlock();

		getVisualiser()->removeShape("Cylinder");
		getVisualiser()->addCylinder(cylinder_coeff, "Cylinder");
	}
}
