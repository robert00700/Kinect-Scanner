
#import <iostream>
#import "ScanTypes.h"
#include "Coctree.h"
#include <vector>
#include <pcl/io/pcd_io.h>

#define log(X) std::cout << X << std::endl;


int main(int argc, char ** argv) {
	if(argc != 2) {
		log("Usage: coctreetest [filename]");
		return 1;
	}
	else {
		std::string file(argv[1]);
		pcl::PCDReader read;
		PointCloud cloud;
		if(!read.read(file, cloud)) {

			PointCloud cloud2;



			Coctree t(0.25, 0.4, cloud);


			log(t.searchClosestIndex(cloud[0], 0.001));

			//log(out[0]);

		}
		else {
			log("Read error");
			return 1;
		}
	}
}
