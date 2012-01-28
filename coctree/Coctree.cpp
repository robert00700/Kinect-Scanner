/*
 * Coctree.cpp
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#include "Coctree.h"

Coctree::Coctree(double radius, double height, PointCloud& input) {
	root = new CoctreeElement(radius, height);

	//Iterate through and add points
	PointCloud::iterator it = input.begin();
	int index = 0;
	while(it != input.end()) {
		//Add indexes for retrieval later
		root->addPendingElement(CoctreePoint(*it, index));
		index++;
		it++;
	}

	//flush the elements through the system!
	root->processPendingElements();
}

void Coctree::search(CoctreePoint point, double dr, double dh, double dtheta, std::vector<CoctreePoint>& out) {
	root->search(point, dr, dh, dtheta, out);
}

void Coctree::searchIndexes(XYZRGB point, double dr, double dh, double dtheta, std::vector<int>& out) {
	std::vector<CoctreePoint> points;

	//first, we do a normal search
	search(CoctreePoint(point, -1), dr, dh, dtheta, points);

	//then we rip out all of the indexes
	std::vector<CoctreePoint>::iterator it = points.begin();
	while(it != points.end()) {
		out.push_back(it->index);
		it++;
	}
}


double squareDistance(CoctreePoint p, CoctreePoint other, double angleCoefficient) {
	double dr = fabs(p.radius - other.radius);
	double dh = fabs(p.height - other.height);
	double dtheta = fmod(p.radius - other.radius, TWO_PI);
	if(dtheta > TWO_PI / 2.0) dtheta = TWO_PI - dtheta;
	return dtheta * angleCoefficient * dtheta * angleCoefficient + dr * dr + dh * dh;
}

int Coctree::searchClosestIndex(XYZRGB point, double angleCoefficient) {
	std::vector<CoctreePoint> out;
	CoctreePoint p(point);
	Coctree::search(p, 0.01, 0.01, 0.07, out);

	CoctreePoint best;
	best.index = -1;
	double bestDistance = 10000000.0; //infinity

	std::vector<CoctreePoint>::iterator it = out.begin();
	while(it != out.end()) {
		CoctreePoint test = *it;
		//A hacky equality check
		if(test.radius != p.radius && test.theta != p.theta && test.height != p.height) {
			double testDistance = squareDistance(p, test, angleCoefficient);
			if(testDistance < bestDistance) {
				best = test;
				bestDistance = testDistance;
			}
		}
		it++;
	}

	return best.index;
}

Coctree::~Coctree() {
	delete root;
}

