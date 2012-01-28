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
#include "process/TurntableProcess.h"
#include "filter/CylinderOcclusionFilter.h"
#include "filter/TurntableCoordinateFilter.h"
#include "process/ICPRotationProcess.h"
#include "filter/MatrixFilter.h"
#include "gui/PointCloudVisualiser.h"
#include "gui/TurntableCalibrationVisualiser.h"
#include "filter/BackgroundFilter.h"
#include "process/AverageProcess.h"

boost::mutex mutex_;

//PointCloudVisualiser v;

Vector lastpos;

int upcnt = 0;
int downcnt = 0;
int rightcnt = 0;
int leftcnt = 0;

struct EventHelper
{
  void cloud_cb (const PointCloud::ConstPtr & cloud) {
	  PointCloud * processCloud = new PointCloud(*cloud);

	  //Cull background
	  BackgroundFilter bg(0.8);
	  bg.filterPointCloud(*processCloud);

	  //Perform averaging
	  AverageProcess avg;
	  avg.processPointCloud(*processCloud);
	  Vector pos = avg.getAverage();



	  float speed = 0.05;
	  int iterations = 2;
	  Vector vel = lastpos - pos;
	  //std::cout << vel.x << std::endl;
	  if(vel.x > speed) {
		  rightcnt++;
		  if(rightcnt > iterations) {
			  system("xdotool key control+alt+Right");
			  rightcnt -= 10;
		  }
	  }
	  else {
		  rightcnt = 0;
	  }

	  if(vel.x < -speed) {
	  		  leftcnt++;
	  		  if(leftcnt > iterations) {
	  			system("xdotool key control+alt+Left");
	  			  leftcnt -= 10;
	  		  }
	  	  }
	  	  else {
	  		  leftcnt = 0;
	  	  }

	  if(vel.y < -speed) {
	 	  		  upcnt++;
	 	  		  if(upcnt > iterations) {
	 	  			system("xdotool key control+alt+Down");
	 	  			  upcnt -= 10;
	 	  		  }
	 	  	  }
	 	  	  else {
	 	  		  upcnt = 0;
	 	  	  }

	  if(vel.y > speed) {
	 	 	  		  downcnt++;
	 	 	  		  if(downcnt > iterations) {
	 	 	  			system("xdotool key control+alt+Up");
	 	 	  			  downcnt -= 10;
	 	 	  		  }
	 	 	  	  }
	 	 	  	  else {
	 	 	  		  downcnt = 0;
	 	 	  	  }

	  lastpos = pos;

	  //v.updateObject(*processCloud);

	  delete processCloud;
  }
};

void loop() {
  while(true) {
  }
}

int main(int argc, char ** argv) {
 std::cout << argv[0];
  pcl::Grabber* interface = new pcl::OpenNIGrabber ("");

  EventHelper h;
  boost::function<void(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr&) > f = boost::bind (&EventHelper::cloud_cb, &h, _1);
  boost::signals2::connection c1 = interface->registerCallback (f);

  interface->start ();
  loop();
  interface->stop ();
}
