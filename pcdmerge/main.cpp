#import <iostream>
#import "ScanTypes.h"
#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>
#include "filter/XZRotationFilter.h"
#include "process/ICPRotationProcess.h"
#include "filter/RotationFilter.h"
#include "gui/PointCloudVisualiser.h"

#define log(X) std::cout << X << std::endl;

int main(int argc, char ** argv) {
	if(argc != 6) {
		log("Usage: pcdjson [main.pcd] [additional.pcd] xrot yrot zrot");
		return 1;
	}
	else {
		PointCloudVisualiser v;

		std::string fileMain(argv[1]);
		std::string fileAdditional(argv[2]);

		pcl::PCDReader read;

		RotationFilter lad(RotationFilter::ROTATE_YZ ,3.14159);
		ICPRotationProcess icprot;

		PointCloud * cloudMain = new PointCloud();
		PointCloud * cloudAdditional = new PointCloud();
		PointCloud * result = new PointCloud();

		PointCloud::ConstPtr ptrMain(cloudMain);
		PointCloud::ConstPtr ptrAdditional(cloudAdditional);

		if(!read.read(fileMain, *cloudMain) && !read.read(fileAdditional, *cloudAdditional)) {
			//lad.filterPointCloud(*cloudAdditional);
			log("Starting merge");
			pcl::IterativeClosestPoint<XYZRGB, XYZRGB> icp;
			icp.setInputTarget(ptrMain);
			icp.setInputCloud(ptrAdditional);


			 // Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
			 icp.setMaxCorrespondenceDistance (0.1);
			 // Set the maximum number of iterations (criterion 1)
			 icp.setMaximumIterations (5000);
			 // Set the transformation epsilon (criterion 2)
			 icp.setTransformationEpsilon (1e-8);

			//icp.align(*result);
			log("Merge complete");


			icprot.setModel(*cloudAdditional);
			icprot.fuseModel(*cloudMain);

			v.updateObject(icprot.getModel());
			int x;
			while(1) {
				x++;
			}
			//Start iteration loop
			//Perform translation
			//Perform rotation
			//Keep going until we reach a point we are happy with
		}
		else {
			log("PCD file read error");
		}
	}
}
