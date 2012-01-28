/*
 * ICPRotationProcess.cpp
 *
 *  Created on: 30 Oct 2011
 *      Author: rob
 */

#include "ICPRotationProcess.h"
#include "filter/MatrixFilter.h"
#include "filter/XZRotationFilter.h"
#include "filter/OutlierFilter.h"
#include "process/NormalEstimationProcess.h"
#include <math.h>

ICPRotationProcess::ICPRotationProcess(float m) {
	// TODO Auto-generated constructor stub
	max = m;
	theta = 0.0f;
}


/* Vector ICPRotationProcess::getClosestPoint(Vector in) {
	PointCloud::iterator it = model.begin();
	Vector bestPoint;
	bool found = false;
	while(it != model.end()) {
		Vector test(it->x, it->y, it->z);
		if(found) {
			if(in.dist(bestPoint) > in.dist(test)) {
				bestPoint = test;
			}
		}
		else {
			bestPoint = test;
			found = true;
		}
		it++;
	}
	return bestPoint;
} */


Vector ICPRotationProcess::getClosestPoint(Vector p) {
	std::vector<int> index;
	std::vector<float> distance;
	XYZRGB pi;
	pi.x = p.x;
	pi.y = p.y;
	pi.z = p.z;
	tree.nearestKSearch(pi, 1, index, distance);
	XYZRGB out = model[index[0]];
	return Vector(out.x, out.y, out.z);
}

int ICPRotationProcess::getClosestPointIndex(Vector p) {
	std::vector<int> index;
	std::vector<float> distance;
	XYZRGB pi;
	pi.x = p.x;
	pi.y = p.y;
	pi.z = p.z;
	tree.nearestKSearch(pi, 1, index, distance);
	return index[0];
}

void ICPRotationProcess::fuseModel(const PointCloud & in) {
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

void ICPRotationProcess::recalculateModelNormals() {
	//Caclulate new normals
		NormalEstimationProcess nep(0.02f);
		nep.processPointCloud(model);
		modelNormals = PointCloudNormals(nep.getNormals());
}

float ICPRotationProcess::getNewTheta(const PointCloud & input) {
	//Take a mutable copy
	PointCloud in(input);

	XZRotationFilter f(theta);
	f.filterPointCloud(in);

	//Caclulate new normals
	NormalEstimationProcess nep(0.06f);
	nep.processPointCloud(in);
	PointCloudNormals inputNormals = nep.getNormals();

	//in is now rotated to our best guess of theta so far

	//accumuator for resolution coefficients
	float resolutionCoefficientTop = 0.0f;
	float resolutionCoefficientBottom = 0.0f;

	PointCloud::iterator it = in.begin();
	int ct = 0;
	int index = 0;
	int siz = in.size();

	Vector p;
	Vector c;
	//#pragma omp parallel for private(it, p, c) reduction(+:resolutionCoefficientTop) reduction(+:resolutionCoefficientBottom) reduction(+:ct)
	for(index = 0; index < siz; index++) {
		XYZRGB it = in[index];
		pcl::Normal norm = inputNormals[index];

		//std::cout << "processing:" << ct <<std::endl;
		//p = current point, c is closest point
		p = Vector(it.x, it.y, it.z);
		Vector pNormal = Vector(norm.normal_x, norm.normal_y, norm.normal_z);
		int i = getClosestPointIndex(p);

		XYZRGB point = model[i];
		pcl::Normal pointNormal = modelNormals[i];

		Vector c(point.x, point.y, point.z);
		Vector cNormal(pointNormal.normal_x, pointNormal.normal_y, pointNormal.normal_z);

		//std::cout << c.dist(p) << std::endl;
		//If we go over the max distance, ignore
		if(p.dist(c) < max && pNormal.angle(cNormal) < 20.0f * TO_RAD) {
			//calculate particular resolution coefficient
			float coefficientTop = (p.z * c.x  - p.x * c.z);
			float coefficientBottom = (p.x * c.x + p.z * c.z);

			//float weighting = 1.0f;
			float weighting = pNormal * cNormal;
			//float weighting = 1.0f - (p.dist(c) / max);
			resolutionCoefficientTop += coefficientTop * weighting;
			resolutionCoefficientBottom += coefficientBottom * weighting;
			ct++;
		}
	}

	///Work out new theta
	if(ct > 0) {
		float dtheta = atan(resolutionCoefficientTop / resolutionCoefficientBottom);
		theta = theta - ((fabs(dtheta) > TO_RAD * 0.1f) ? TO_RAD * 0.1f * (dtheta / fabs(dtheta)) : dtheta);
	}
	ready = true;
}

ICPRotationProcess::~ICPRotationProcess() {
	// TODO Auto-generated destructor stub
}

void ICPRotationProcess::processPointCloud(const PointCloud & in)
{
	getNewTheta(in);
}


