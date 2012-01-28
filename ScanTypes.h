/*
 * ScanTypes.h
 *
 *  Created on: 23 Oct 2011
 *      Author: rob
 */

#ifndef SCANTYPES_H_
#define SCANTYPES_H_

#include <pcl/common/common.h>
#include <pcl/PolygonMesh.h>
#include "vector/Vector.h"
#include <Eigen/Dense>
#include <string>
#include <sstream>
#include <iostream>

#define TO_DEG (180.0f / 3.1415926f)
#define TO_RAD (3.1415926f / 180.0f)

#define TWO_PI (3.141592653589793 * 2.0)
#define PI 3.141592635389793

template <class T>
bool from_string(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloud;
typedef pcl::PointXYZRGB XYZRGB;
typedef pcl::PointXYZRGBNormal XYZRGBNormals;
typedef pcl::PolygonMesh PolyMesh;
typedef pcl::PointCloud<pcl::Normal> PointCloudNormals;
typedef pcl::PointCloud<XYZRGBNormals> PointCloudPlusNormals;

typedef Eigen::Matrix4f Matrix4;
typedef Eigen::Vector4f Vector4;
typedef Vector Vector3;

#endif /* SCANTYPES_H_ */
