/*
 * RecordingSession.cpp
 *
 *  Created on: 17 Jan 2012
 *      Author: rob
 */

#include "RecordingSession.h"
#include <iostream>
#include <time.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>

RecordingSession::RecordingSession(std::string d) {
	directory = d;
	started = false;
}

void RecordingSession::saveFrame(PointCloud& cloud) {
	 timeval tv;
	  gettimeofday(&tv, NULL);
	  double ti = (double)tv.tv_sec + ((double)tv.tv_usec / 1000000.0);
	  if(!started) {
			started = true;
			start = ti;
		 }

	std::stringstream timeString;
	timeString.setf(std::ios::fixed,std::ios::floatfield);
	timeString << (ti - start);

	std::stringstream place;
	place << directory << "/" << timeString.str();

	pcl::PCDWriter write;
	write.writeBinary(place.str(), cloud);
}

RecordingSession::~RecordingSession() {
	// TODO Auto-generated destructor stub
}

