#import <iostream>
#import "ScanTypes.h"
#include <pcl/io/pcd_io.h>

#define log(X) std::cout << X << std::endl;

std::stringstream ss;

void point2json(XYZRGB in) {
	ss << "{";
	ss << "x:" << in.x << ",";
	ss << "y:" << in.y << ",";
	ss << "z:" << in.z << ",";
	ss << "r:" << (int)in.r << ",";
	ss << "g:" << (int)in.g << ",";
	ss << "b:" << (int)in.b;
	ss << "}" << std::endl;
}

int main(int argc, char ** argv) {
	if(argc != 2) {
		log("Usage: pcdjson [filename]");
		return 1;
	}
	else {
		std::string file(argv[1]);
		pcl::PCDReader read;
		PointCloud cloud;
		if(!read.read(file, cloud)) {
			PointCloud::iterator it;
			ss << "var data = [" << std::endl;
			bool first = true;
			for(it = cloud.begin(); it != cloud.end(); it++) {
				if(first) {
					first = false;
				}
				else {
					ss << ",";
				}
				point2json(*it);
			}
			ss << "];";
			log(ss.str());
		}
		else {
			log("Read error");
			return 1;
		}
	}
}
