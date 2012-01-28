/*
 * PolyMeshVisualiser.h
 *
 *  Created on: 21 Nov 2011
 *      Author: rob
 */

#ifndef POLYMESHVISUALISER_H_
#define POLYMESHVISUALISER_H_

#include "Visualiser.h"

class PolyMeshVisualiser : public Visualiser<PolyMesh> {
protected:
	void drawObject();
public:
	PolyMeshVisualiser(std::string name="Visualiser") : Visualiser<PolyMesh>(name) {}
	PolyMeshVisualiser(PolyMesh in, std::string name="Visualiser") : Visualiser<PolyMesh>(in, name) {}
};

#endif /* POLYMESHVISUALISER_H_ */
