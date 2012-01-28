/*
 * MatrixFilter.h
 *
 *  Created on: 31 Oct 2011
 *      Author: rob
 */

#ifndef MATRIXFILTER_H_
#define MATRIXFILTER_H_

#include "PointCloudFilter.h"
#include "ScanTypes.h"

class MatrixFilter: public PointCloudFilter {
private:
	Matrix4 transform;
public:
	MatrixFilter(Matrix4 & in);
	virtual void filterPointCloud(PointCloud & in);
	virtual ~MatrixFilter();
};

#endif /* MATRIXFILTER_H_ */
