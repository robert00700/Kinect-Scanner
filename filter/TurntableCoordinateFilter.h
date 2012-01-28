/*
 * TurntableCoordinateFilter.h
 *
 *  Created on: 24 Oct 2011
 *      Author: rob
 */

#ifndef TURNTABLECOORDINATEFILTER_H_
#define TURNTABLECOORDINATEFILTER_H_

#include "PointFilter.h"

class TurntableCoordinateFilter: public PointCloudFilter {
private:
	Matrix4 transform;
public:
	TurntableCoordinateFilter();
	TurntableCoordinateFilter(Vector pos, Vector up, Vector fwd, Vector side);
	virtual ~TurntableCoordinateFilter();
	virtual void filterPointCloud(PointCloud & in);
};

#endif /* TURNTABLECOORDINATEFILTER_H_ */
