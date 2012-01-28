/*
 * TurntableProcess.cpp
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#include "TurntableProcess.h"
#include "AverageProcess.h"
#include "PlaneProcess.h"
#include "../filter/ColorFilter.h"
#include "filter/DistanceFromPointFilter.h"

TurntableProcess::~TurntableProcess() {
	// TODO Auto-generated destructor stub
}

TurntableProcess::TurntableProcess(float _distance, Vector _color, float _accuracy)
{
	distance = _distance;
	color = _color;
	accuracy = _accuracy;
}

void TurntableProcess::processPointCloud(const PointCloud & in)
{
	PointCloud copy(in);
	ColorFilter cf(color, accuracy);
	cf.filterPointCloud(copy);

	//std::cout << "Filtering " << color.x << " " << color.y << " " << color.z << std::endl;

	AverageProcess avg;
	avg.processPointCloud(copy);
	if(avg.isReady()) {
		position = avg.getAverage();
		PlaneProcess pln(position, distance);

		pln.processPointCloud(copy);
		if(pln.isReady()) {

			up = pln.getNormal().norm();

		    //Work out the 'pointing to you' vector
		    float gradient = up.z / up.y;
		    float fz = -sqrt(1.0 / (gradient * gradient + 1));
		    float fy = -gradient * fz;
		    fwd = Vector3(0.0f, fy, fz).norm(); //X is zero as we are pointing at the camera
		    side = (up % fwd).norm(); //cross
			ready = true;
		}
		else {
			ready = false;
		}
	}
	else {
		ready = false;
	}
}


