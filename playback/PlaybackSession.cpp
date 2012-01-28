/*
 * PlaybackSession.cpp
 *
 *  Created on: 17 Jan 2012
 *      Author: rob
 */

#include "PlaybackSession.h"

#include <pcl/io/pcd_io.h>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

PlaybackSession::PlaybackSession(std::string dir) {
	getDirectoryList(dir, fileList);
	directory = dir;
}

PlaybackSession::~PlaybackSession() {

}

void PlaybackSession::getFrame(int index, PointCloud& cloud) {
	int size = fileList.size();
	if(index >= size) index = size - 1; //this will probably break at some point

	std::stringstream place;
	place << directory << "/" << fileList[index];

	pcl::PCDReader r;
	r.read(place.str(), cloud);
}


bool sortFiles (std::string i,std::string j) {
	float ii, jj;
	from_string<float>(ii, i, std::dec);
	from_string<float>(jj, j, std::dec);
	return (ii<jj);
}

int PlaybackSession::getDirectoryList (std::string dir, std::vector<std::string> &files)
{
	using namespace std;
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        if(dirp->d_name[0] != '.') {
        	files.push_back(string(dirp->d_name));
        }
    }
    closedir(dp);
    sort(files.begin(), files.end(), sortFiles);
    return 0;
}
