/*
 * Coctree.h
 *
 *  Created on: 24 Jan 2012
 *      Author: rob
 */

#ifndef COCTREE_H_
#define COCTREE_H_

#include "ScanTypes.h"
#include "CoctreeElement.h"

class Coctree {
private:
	CoctreeElement * root;
public:
	//Constructor takes a pointcloud vector
	Coctree(double radius, double height, PointCloud& input);
	void search(CoctreePoint point, double dr, double dh, double dtheta, std::vector<CoctreePoint>& out);
	void searchIndexes(XYZRGB point, double dr, double dh, double dtheta, std::vector<int>& out);
	int searchClosestIndex(XYZRGB point, double angleCoefficient);
	virtual ~Coctree();
};

#endif /* COCTREE_H_ */
