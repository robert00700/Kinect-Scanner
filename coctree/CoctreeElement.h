/*
 * CoctreeElement.h
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#ifndef COCTREEELEMENT_H_
#define COCTREEELEMENT_H_

#include <vector>
#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>



#include "CoctreePoint.h"

#define TWO_PI (3.141592653589793 * 2.0)

struct limits {
	double min;
	double max;
	limits(double _min = 0.0, double _max = 0.0) {
		min = _min;
		max = _max;
	}
	limits generateLower() {
		return limits(min, min + (max - min) / 2.0);
	}
	limits generateUpper() {
		return limits(max - (max - min) / 2.0, max);
	}
	bool isUpper(double test) {
		return test > min + ((max - min) / 2.0);
	}
};


class CoctreeElement {
private:
	limits radius;
	limits height;
	limits angle;

	std::vector <CoctreeElement*> children;

	//Used in the construction of the tree
	std::vector<CoctreePoint> pendingElements;
	void subdivide();
	int calculateChildOffset(CoctreePoint p);


	//Stores the final item (if there is one!), and whether we are a leaf, and if so, if we are empty
	CoctreePoint item;
	bool empty;
	bool leaf;

public:
	CoctreeElement(double _radius, double _height);

	inline void addPendingElement(CoctreePoint in) {
		pendingElements.push_back(in);
	}
	void processPendingElements();

	CoctreeElement(limits radius, limits height, limits angle);
	void search(CoctreePoint point, double dr, double dh, double dtheta, std::vector<CoctreePoint>& out);
	virtual ~CoctreeElement();
};

#endif /* COCTREEELEMENT_H_ */
