#import <iostream>
#import "ScanTypes.h"
#include <pcl/io/pcd_io.h>

#define log(X) std::cout << X << std::endl;

std::stringstream ss;

void point2ply(XYZRGB in) {
	ss << in.x << " " << in.y << " " << in.z << " " << (int)in.r << " " << (int)in.g << " " << (int)in.b << std::endl;
}

/*
 * PLY output:
function WritePointCloud( pointCloud, colour, fileName )
%WRITEPOINTCLOUD Summary of this function goes here
%   Detailed explanation goes here
fc = fopen(fileName, 'w');
fprintf(fc, 'ply\n');
fprintf(fc, 'format ascii 1.0\n');
fprintf(fc, 'comment : created from Kinect depth image\n');
fprintf(fc, 'element vertex %d\n',size(pointCloud,1));
fprintf(fc, 'property float x\n');
fprintf(fc, 'property float y\n');
fprintf(fc, 'property float z\n');
fprintf(fc, 'property uint8 red\n');
fprintf(fc, 'property uint8 green\n');
fprintf(fc, 'property uint8 blue\n');
fprintf(fc, 'end_header\n');
for i=1:size(pointCloud,1)

    fprintf(fc, '%f %f %f %d %d %d \n', pointCloud(i,1), pointCloud(i,2), pointCloud(i,3), colour(i,1), colour(i,2), colour(i,3));

end
 */

int main(int argc, char ** argv) {
	if(argc != 2) {
		log("Usage: pcdply [filename]");
		return 1;
	}
	else {
		std::string file(argv[1]);
		pcl::PCDReader read;
		PointCloud cloud;
		if(!read.read(file, cloud)) {
			PointCloud::iterator it;
			ss << "ply" << std::endl;
			ss << "format ascii 1.0" << std::endl;
			ss << "comment : created from Kinect depth image" << std::endl;
			ss << "element vertex " << cloud.size() << std::endl;
			ss << "property float x" << std::endl;
			ss << "property float y" << std::endl;
			ss << "property float z" << std::endl;
			ss << "property uint8 red" << std::endl;
			ss << "property uint8 green" << std::endl;
			ss << "property uint8 blue" << std::endl;
			ss << "end_header" << std::endl;

			bool first = true;
			for(it = cloud.begin(); it != cloud.end(); it++) {
				point2ply(*it);
			}
			log(ss.str());
		}
		else {
			log("Read error");
			return 1;
		}
	}
}
