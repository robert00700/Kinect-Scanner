/*
 * CoctreeElement.cpp
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#include "CoctreeElement.h"

#define printLimit(X) " (" << X.min << ", " << X.max << ") "

CoctreeElement::CoctreeElement(limits _radius, limits _height, limits _angle) {
	radius = _radius;
	height = _height;
	angle = _angle;
	//log("Creating CoctreeElement " << "r:" << printLimit(radius) << " h:" << printLimit(height) << " a:" << printLimit(angle));
}

CoctreeElement::CoctreeElement(double _radius, double _height) {
	radius = limits(0.0, _radius);
	height = limits(0.0, _height);
	angle = limits(0.0, TWO_PI);
	//log("Creating Root CoctreeElement " << "r:" << printLimit(radius) << " h:" << printLimit(height) << " a:" << printLimit(angle));
}

void CoctreeElement::processPendingElements() {
	int size = pendingElements.size();
	//log("SIZE :: " << size);

	//Depending on how many elements arrived in our pigeon hole, do stuff
	switch(size) {
	case 0:
		leaf = true;
		empty = true;
		break;
	case 1:
		leaf = true;
		empty = false;
		item = pendingElements[0];
		break;
	default:
		leaf = false;
		empty = false;
		subdivide();
	}
}

void CoctreeElement::subdivide() {
#define L0 generateLower()
#define L1 generateUpper()

	limits r = radius;
	limits h = height;
	limits a = angle;

	//Generate all of the children in a trendy trendy binary manner
	children.push_back(new CoctreeElement(r.L0, h.L0, a.L0));
	children.push_back(new CoctreeElement(r.L1, h.L0, a.L0));
	children.push_back(new CoctreeElement(r.L0, h.L1, a.L0));
	children.push_back(new CoctreeElement(r.L1, h.L1, a.L0));
	children.push_back(new CoctreeElement(r.L0, h.L0, a.L1));
	children.push_back(new CoctreeElement(r.L1, h.L0, a.L1));
	children.push_back(new CoctreeElement(r.L0, h.L1, a.L1));
	children.push_back(new CoctreeElement(r.L1, h.L1, a.L1));

	while(!pendingElements.empty()) {
		CoctreePoint p = pendingElements.back();
		pendingElements.pop_back();

		//post the child into the correct pigeonhole
		children[calculateChildOffset(p)]->addPendingElement(p);
	}

	std::vector<CoctreeElement*>::iterator it = children.begin();
	while(it != children.end()) {
		(*it)->processPendingElements();
		it++;
	}
}


int CoctreeElement::calculateChildOffset(CoctreePoint p) {
	//use tests on the various dimensions to calculate child offset
	int offset = 0;
	if(radius.isUpper(p.radius)) offset += 1;
	if(height.isUpper(p.height)) offset += 2;
	if(angle.isUpper(p.theta)) offset += 4;
	return offset;
}

void CoctreeElement::search(CoctreePoint point, double dr, double dh, double dtheta, std::vector<CoctreePoint>& out) {
	if(!empty) {
		if(leaf) {
			//Do a specific search
			//TODO-FIX THETA
			//log("CHECKING LEAF " << "r:" << printLimit(radius) << " h:" << printLimit(height) << " a:" << printLimit(angle));
			//log("ITEM theta=" << item.theta << " radius=" << item.radius << " height=" << item.height);
			if(fmod(fabs(item.theta - point.theta), TWO_PI) < dtheta && fabs(item.height - point.height) < dh && fabs(item.radius - point.radius) < dr) {
				//log("FOUND")
				out.push_back(item);
			}
		}
		else {
			//Need to find out which locations we need to probe
			//TODO- Find locations to probe
			bool checkUpperHeight = false;
			bool checkLowerHeight = false;
			bool checkUpperRadius = false;
			bool checkLowerRadius = false;
			bool checkUpperAngle = false;
			bool checkLowerAngle = false;

			//Work out what nodes to go to
			if(height.isUpper(point.height + dh)) checkUpperHeight = true;
			if(!height.isUpper(point.height - dh)) checkLowerHeight = true;

			if(radius.isUpper(point.radius + dr)) checkUpperRadius = true;
			if(!radius.isUpper(point.radius - dr)) checkLowerRadius = true;

			if(!angle.isUpper(fmod(point.theta + dtheta, TWO_PI))) checkUpperAngle = true;
			if(angle.isUpper(fmod(point.theta + dtheta, TWO_PI))) checkLowerAngle = true;

			//assume dtheta between 0 and 2pi
			float min1 = fmod(point.theta - dtheta, TWO_PI);
			float min2 = fmod(point.theta + dtheta, TWO_PI);
			if(!angle.isUpper(min1) || !angle.isUpper(min2)) checkLowerAngle = true;

			float max1 = fmod(point.theta + dtheta, TWO_PI);
			float max2 = fmod(point.theta - dtheta, TWO_PI);
			if(angle.isUpper(max1) || angle.isUpper(max2)) checkUpperAngle = true;

			std::vector<int> searchPlaces;
			if(checkLowerRadius && checkLowerHeight && checkLowerAngle) searchPlaces.push_back(0);
			if(checkUpperRadius && checkLowerHeight && checkLowerAngle) searchPlaces.push_back(1);
			if(checkLowerRadius && checkUpperHeight && checkLowerAngle) searchPlaces.push_back(2);
			if(checkUpperRadius && checkUpperHeight && checkLowerAngle) searchPlaces.push_back(3);
			if(checkLowerRadius && checkLowerHeight && checkUpperAngle) searchPlaces.push_back(4);
			if(checkUpperRadius && checkLowerHeight && checkUpperAngle) searchPlaces.push_back(5);
			if(checkLowerRadius && checkUpperHeight && checkUpperAngle) searchPlaces.push_back(6);
			if(checkUpperRadius && checkUpperHeight && checkUpperAngle) searchPlaces.push_back(7);

			std::vector<int>::iterator it = searchPlaces.begin();
			while(it != searchPlaces.end()) {
				children[*it]->search(point, dr, dh, dtheta, out);
				it++;
			}
		}
	}
	else {
		//log("CHECKING EMPTY " << "r:" << printLimit(radius) << " h:" << printLimit(height) << " a:" << printLimit(angle));
	}
}

CoctreeElement::~CoctreeElement() {
	while(!children.empty()) {
		delete children.back();
		children.pop_back();
	}
}

