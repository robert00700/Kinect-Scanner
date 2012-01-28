/*
 * RecordingSession.h
 *
 *  Created on: 17 Jan 2012
 *      Author: rob
 */

#ifndef RECORDINGSESSION_H_
#define RECORDINGSESSION_H_

#include "ScanTypes.h"

class RecordingSession {
private:
	std::string directory;
	bool started;
	double start;
public:
	RecordingSession(std::string d);
	virtual ~RecordingSession();
	void saveFrame(PointCloud& cloud);
};

#endif /* RECORDINGSESSION_H_ */
