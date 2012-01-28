#import <iostream>
#import "ScanTypes.h"
#include <pcl/io/pcd_io.h>
#include <pcl/common/common.h>
#include <pcl/common/time.h> //fps calculations
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/openni_grabber.h>
#include <cfloat>
#include <pcl/visualization/point_cloud_handlers.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
//#include <pcl/visualization/histogram_visualizer.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

//armadillo linear algebra library
#include <armadillo>

//to look for isnan
#include <math.h>
#include <time.h>

#include "filter/CylinderOcclusionFilter.h"
#include "filter/TurntableCoordinateFilter.h"
#include "gui/PointCloudNormalVisualiser.h"
#include "playback/RecordingSession.h"
#include "playback/PlaybackSession.h"
#include "filter/OutlierFilter.h"
#include "process/NormalEstimationProcess.h"
#include "calibration/CalibrationManager.h"

#define log(X) std::cout << X << std::endl;

PointCloudNormalVisualiser v;

int main(int argc, char ** argv) {
	if(argc != 2) {
		log("Usage: playback [directory]");
		v.die();
		return 1;
	}
	else {
		//Load the directory
		PlaybackSession s = PlaybackSession(std::string(argv[1]));
		if(s.size() == 0) {
			log("Nothing to play!");
			v.die();
			return 1;
		}
		else
		{
			OutlierFilter out(1.0f);
			NormalEstimationProcess p(0.1f);

			int index = 0;
			PointCloud cloud;
			while(index < s.size()) {
				s.getFrame(index, cloud);
				out.filterPointCloud(cloud);

				p.processPointCloud(cloud);

				v.updateObject(cloud);
				v.setNormals(p.getNormals());

				boost::this_thread::sleep(boost::posix_time::milliseconds(200));
				index++;
			}
		}
		v.die();
		log("Done!");
	}
}
