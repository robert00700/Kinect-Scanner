/*
 * PlaybackSession.h
 *
 *  Created on: 17 Jan 2012
 *      Author: rob
 */

#ifndef PLAYBACKSESSION_H_
#define PLAYBACKSESSION_H_
#include "ScanTypes.h"


class PlaybackSession {
private:
	int getDirectoryList(std::string dir, std::vector<std::string>& out);
	std::vector<std::string> fileList;
	std::string directory;
public:
	PlaybackSession(std::string dir);
	int size() {
		return fileList.size();
	}
	std::string getFile(int index) {
		return fileList[index];
	}
	void getFrame(int index, PointCloud& out);
	virtual ~PlaybackSession();
};

#endif /* PLAYBACKSESSION_H_ */
