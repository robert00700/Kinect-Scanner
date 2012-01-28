/*
 * BackgroundFilter.h
 *
 *  Created on: 5 Dec 2011
 *      Author: rob
 */

#ifndef BACKGROUNDFILTER_H_
#define BACKGROUNDFILTER_H_

#include "PointFilter.h"

#define DEFAULT_DEPTH 0.5f

class BackgroundFilter: public PointFilter {
private:
	float depth;
public:
	BackgroundFilter(float depth = DEFAULT_DEPTH);
	virtual ~BackgroundFilter();
	virtual bool filterPoint(XYZRGB & in);
};

#endif /* BACKGROUNDFILTER_H_ */
