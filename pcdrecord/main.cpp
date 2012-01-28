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
#include "gui/PointCloudVisualiser.h"
#include "playback/RecordingSession.h"
#include "calibration/CalibrationManager.h"

#define log(X) std::cout << X << std::endl;

std::string directory;
CylinderOcclusionFilter cylinderFilter;
TurntableCoordinateFilter turntableCoordinateFilter;
PointCloudVisualiser v;
RecordingSession r("");

bool isRecording = false;

struct EventHelper
{
  void cloud_cb (const PointCloud::ConstPtr & cloud) {
	  PointCloud * processCloud = new PointCloud(*cloud);

	  cylinderFilter.filterPointCloud(*processCloud);
	  turntableCoordinateFilter.filterPointCloud(*processCloud);

	  if(isRecording) {
		  log("Saving frame");
		  r.saveFrame(*processCloud);
	  }

	  if(processCloud->size() > 0) v.updateObject(*processCloud);

	  delete processCloud;
  }
};

int main(int argc, char ** argv) {
	if(argc != 3) {
		log("Usage: record [config] [directory]");
		v.die();
		return 1;
	}
	else {
		directory = std::string(argv[2]);
		r = RecordingSession(directory);

		CalibrationManager c = CalibrationManager(std::string(argv[1]));
		cylinderFilter = CylinderOcclusionFilter(c.getPosition(), c.getUp(), c.getHeight(), c.getRadius());
		turntableCoordinateFilter = TurntableCoordinateFilter(c.getPosition(), c.getUp(), c.getFwd(), c.getSide());

	  //Set up OpenNI
	  pcl::Grabber* interface = new pcl::OpenNIGrabber ("");
	  EventHelper h;
	  boost::function<void(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr&) > f = boost::bind (&EventHelper::cloud_cb, &h, _1);
	  boost::signals2::connection c1 = interface->registerCallback (f);

	  //Set stuff up
	 interface->start ();

	  log("Ready to record to " << directory << " press any key to start");
	  std::cin.get();
	  log("Recording, press any key to stop");
	  isRecording = true;
	  std::cin.get();
	  isRecording = false;
	  v.die();
	  interface->stop();
	  return 0;
	}
}
