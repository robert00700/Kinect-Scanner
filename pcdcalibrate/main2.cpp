//PCL bants
#include <boost/thread/thread.hpp>

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

//color filter
#include "ScanTypes.h"
#include "process/TurntableProcess.h"
#include "filter/CylinderOcclusionFilter.h"
#include "filter/TurntableCoordinateFilter.h"
#include "process/ICPRotationProcess.h"
#include "filter/MatrixFilter.h"
#include "filter/ColorFilter.h"
#include "gui/PointCloudVisualiser.h"
#include "gui/TurntableCalibrationVisualiser.h"
#include "filter/BackgroundFilter.h"
#include "filter/DistanceFromPointFilter.h"
#include "process/AverageProcess.h"
#include "calibration/CalibrationManager.h"

TurntableCalibrationVisualiser v;
float radius;
float height;
float distance;
float colorAccuracy;
std::string configFileName;

Vector currentPos;
Vector currentSide;
Vector currentFwd;
Vector currentUp;

//This is set to true once we have our 'currents' set to something sensible
bool readyToSave = false;
bool flip = false;


struct EventHelper
{
  void cloud_cb (const PointCloud::ConstPtr & cloud) {
	  PointCloud * processCloud = new PointCloud(*cloud);

	  BackgroundFilter bg(distance);
	  bg.filterPointCloud(*processCloud);

	  //Set up turntable detector with ositionselected color
	  Vector col = v.getSelectedColor();
	  TurntableProcess p(radius * 2.0f, col, colorAccuracy);

	  //If a point has been picked, get rolling
	  if(v.hasPickedPoint()) {
		  //Apply color filter for visualisation
		  if(flip) {
		  ColorFilter f = ColorFilter(col, colorAccuracy);
		  f.filterPointCloud(*processCloud);
		  flip = false;
		  }
		  else {
			  flip = true;
		  }

		  v.updateObject(*processCloud);


		  //remove points far away from our selected pos
		  DistanceFromPointFilter dist(v.getSelectedPos(), radius * 2);
		  dist.filterPointCloud(*processCloud);
		  p.processPointCloud(*processCloud);
	  }
	  else {
		  v.updateObject(*processCloud);
	  }

	  if(p.isReady()) {
		  v.updateInfo(p.getPosition(), p.getUp());

		  //update our details to be logged
		  currentPos = p.getPosition();
		  currentUp = p.getUp();
		  currentFwd = p.getFwd();
		  currentSide = p.getSide();
		  readyToSave = true;
	  }

	  delete processCloud;
  }
};

int main(int argc, char ** argv) {
	if(argc != 6) {
		std::cout << "Usage: calibrate [radius] [height] [distance] [colorAccuracy] [output]" << std::endl;
		v.die();
		return 1;
	}

  std::string radiusString(argv[1]);
  std::string heightString(argv[2]);
  std::string distanceString(argv[3]);
  std::string colorString(argv[4]);
  from_string<float>(radius, radiusString, std::dec);
  from_string<float>(height, heightString, std::dec);
  from_string<float>(distance, distanceString, std::dec);
  from_string<float>(colorAccuracy, colorString, std::dec);
  v.setRadius(radius);
  v.setHeight(height);
  std::string configFileName(argv[5]);
  std::cout << "Parsed radius " << radius << " and height " << height << std::endl;

  //Set up OpenNI
  pcl::Grabber* interface = new pcl::OpenNIGrabber ("");
  EventHelper h;
  boost::function<void(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr&) > f = boost::bind (&EventHelper::cloud_cb, &h, _1);
  boost::signals2::connection c1 = interface->registerCallback (f);

  //Set shit up
  interface->start ();

  while(!readyToSave) {
	  std::cout << "Calibrating, press enter when done" << std::endl;
	  std::cin.get();
  }

  std::cout << "Saving to " << configFileName << std::endl;
  //Set up a configuration instance with these new settings
  CalibrationManager m;
  m.setRadius(radius);
  m.setHeight(height);
  m.setPosition(currentPos);
  m.setSide(currentSide);
  m.setFwd(currentFwd);
  m.setUp(currentUp);

  //save down file
  m.save(configFileName);
  delete interface;
  v.die();

  //Success!
  return 0;
}
