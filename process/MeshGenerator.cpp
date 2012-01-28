/*
 * MeshGenerator.cpp
 *
 *  Created on: 2 Dec 2011
 *      Author: rob
 */

#include "MeshGenerator.h"

MeshGenerator::MeshGenerator() {
	mesh.reset();
}

MeshGenerator::~MeshGenerator() {
	mesh.reset();
}

void MeshGenerator::processPointCloud(const PointCloud & in) {
	mesh = generateMesh(in);
}
