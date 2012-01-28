/*
 * PlaneProcess.cpp
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#include "PlaneProcess.h"
#include <armadillo>

using namespace arma;

PlaneProcess::PlaneProcess() {
	// TODO Auto-generated constructor stub

}

PlaneProcess::PlaneProcess(Vector _position, float _distance) {
	position = _position;
	distance = _distance;
}

PlaneProcess::~PlaneProcess() {
	// TODO Auto-generated destructor stub
}

void PlaneProcess::processPointCloud(const PointCloud & in)
{
	PointCloud::const_iterator it = in.begin();

	//Accumulators for linear equations
	Vector planeSolverVector;
	mat planeSolverMatrix(3,3);
	planeSolverMatrix.zeros();

	int n = 0;
	while(it != in.end()) {
		if(!isnan(it->x) && !isnan(it->y) && !isnan(it->z)) {
			Vector p(it->x, it->y, it->z);

			//Holder for coefficients for this point
			mat planeSolverMatrixAccumulator(3,3);
			planeSolverMatrixAccumulator.zeros(3,3);
			Vector3 planeSolverVectorAccumulator;

			if(position.dist(p) < distance) {
				planeSolverMatrixAccumulator(0,0) = p.x * p.x;
				planeSolverMatrixAccumulator(0,1) = p.x * p.y;
				planeSolverMatrixAccumulator(0,2) = p.x;
				planeSolverMatrixAccumulator(1,0) = p.x * p.y;
				planeSolverMatrixAccumulator(1,1) = p.y * p.y;
				planeSolverMatrixAccumulator(1,2) = p.y;
				planeSolverMatrixAccumulator(2,0) = p.x;
				planeSolverMatrixAccumulator(2,1) = p.y;
				planeSolverMatrixAccumulator(2,2) = 1.0;

				planeSolverVectorAccumulator.x = p.x * p.z;
				planeSolverVectorAccumulator.y = p.y * p.z;
				planeSolverVectorAccumulator.z = p.z;

				planeSolverVector += planeSolverVectorAccumulator;
				planeSolverMatrix += planeSolverMatrixAccumulator;
			}
		}
		it++;
	}
	try {
	    vec svec(3);
	    svec(0) = planeSolverVector.x;
	    svec(1) = planeSolverVector.y;
	    svec(2) = planeSolverVector.z;
	    vec solu = solve(planeSolverMatrix, svec);
	    if(solu(0) != 0.0 && solu(1) != 0.0 && solu(2) != 0.0) {
			normal = Vector(solu(0) / 10, solu(1) / 10, -0.1);
			ready = true;
	    }
	    else {
	    	ready = false;
	    }
	}
	catch(std::logic_error e) {
	    ready = false;
	}
	catch(std::runtime_error e) {
		ready = false;
	}
	catch(std::exception e) {
		ready = false;
	}
}


