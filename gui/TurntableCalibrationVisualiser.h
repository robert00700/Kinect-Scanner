/*
 * TurntableCalibrationVisualiser.h
 *
 *  Created on: 25 Oct 2011
 *      Author: rob
 */

#ifndef TURNTABLECALIBRATIONVISUALISER_H_
#define TURNTABLECALIBRATIONVISUALISER_H_

#include "PointCloudVisualiser.h"

class TurntableCalibrationVisualiser: public PointCloudVisualiser {
protected:
	virtual void postDraw();
	//virtual void processCloud(boost::shared_ptr<PointCloud> in);
	Vector position;
	Vector normal;
	float radius;
	float height;
	bool cylinderReady;
	bool hasPickedPointBool;
	Vector selectedColor;
	Vector selectedPos;
	boost::mutex cylinderMutex;
	virtual void pointPicked(int index, Vector pos) {
		hasPickedPointBool = true;
		XYZRGB p = (*object)[0];
		Vector pvec = Vector(0.0f, 0.0f, 0.0f);

		objectMutex.lock();
		PointCloud::iterator it = object->begin();
		while(it != object->end()) {
			XYZRGB test = *it;
			Vector testvec(test.x, test.y, test.z);
			if(pos.dist(testvec) < pos.dist(pvec) &&
				!isnan(testvec.x) && !isnan(testvec.y) && !isnan(testvec.z)) {
				p = test;
				pvec = testvec;
			}
			it++;
		}
		objectMutex.unlock();

		selectedColor.x = (float)p.r;
		selectedColor.y = (float)p.g;
		selectedColor.z = (float)p.b;
		selectedPos = pvec;

		std::cout << "COLOR " << selectedColor.x << " " << selectedColor.y << " " << selectedColor.z << std::endl;
		std::cout << "POS: " << pvec.x << " " << pvec.y << " " << pvec.z << std::endl;
	}
public:
	void setRadius(float r) {
		radius = r;
	}
	void setHeight(float h) {
		height = h;
	}
	bool hasPickedPoint() {
		return hasPickedPointBool;
	}
	Vector getSelectedColor() {
		return selectedColor;
	}
	Vector getSelectedPos() {
		return selectedPos;
	}
	void updateInfo(Vector _position, Vector _normal);
	TurntableCalibrationVisualiser() : PointCloudVisualiser("Turntable Calibration") {
		hasPickedPointBool = false;
		cylinderReady = false;
	}
	virtual ~TurntableCalibrationVisualiser();
};

#endif /* TURNTABLECALIBRATIONVISUALISER_H_ */
