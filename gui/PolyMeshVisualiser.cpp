/*
 * PolyMeshVisualiser.cpp
 *
 *  Created on: 21 Nov 2011
 *      Author: rob
 */

#include "PolyMeshVisualiser.h"

void PolyMeshVisualiser::drawObject() {
	visualiser->removeAllShapes(0);
	visualiser->addPolygonMesh(*object, "Mesh", 1);
}

