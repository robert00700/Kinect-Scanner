/*
 * Visualiser.h
 *
 *  Created on: 21 Nov 2011
 *      Author: rob
 */

#ifndef VISUALISER_H_
#define VISUALISER_H_

#include "ScanTypes.h"
#include <boost/thread/thread.hpp>
#include <pcl/visualization/pcl_visualizer.h>

template <class T>
class Visualiser {
private:
	boost::shared_ptr<boost::thread> t;

	std::string name;
	bool objectChanged;
	bool shouldDie;
	void run() {
		visualiser.reset(new pcl::visualization::PCLVisualizer(name));
		visualiser->registerPointPickingCallback(&Visualiser::pointPick, *this);
		//visualiser->createInteractor();

		while(!shouldDie && !visualiser->wasStopped()) {
			visualiser->spinOnce();

			if(objectChanged) {
				objectMutex.lock();
				drawObject();
				objectChanged = false;
				objectMutex.unlock();
			}

			postDraw();
			boost::this_thread::sleep (boost::posix_time::microseconds (1000));
		}
		//delete &(*visualiser);

		visualiser.reset();
	}
	void pointPick(const pcl::visualization::PointPickingEvent & e, void * cookie) {
		int index = e.getPointIndex();
		float x,y,z;
		e.getPoint(x,y,z);
		pointPicked(index, Vector(x,y,z));
	}
protected:
	boost::mutex objectMutex;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> visualiser;
	bool firstPass;
	boost::shared_ptr<T> object;
	virtual void processObject(boost::shared_ptr<T> object) {}
	virtual void drawObject() = 0;
	virtual void postDraw() {}
	virtual void pointPicked(int index, Vector pos) {}
public:
	Visualiser(std::string _name="Visualiser") {
		shouldDie = false;
		firstPass = true;
		objectChanged = false;
		name = _name;
		t.reset(new boost::thread(boost::bind( &Visualiser::run, this)));
	}
	Visualiser(T& in, std::string _name="Visualiser") {
		shouldDie = false;
		firstPass = true;
		objectChanged = true;
		name = _name;
		object.reset(new T(in));
		t.reset(new boost::thread(boost::bind( &Visualiser::run, this)));
	}

	virtual ~Visualiser() {
	}

	void updateObject(T& in) {
		objectMutex.lock();
		object.reset(new PointCloud(in));
		processObject(object);
		objectChanged = true;
		objectMutex.unlock();
	}

	boost::shared_ptr<pcl::visualization::PCLVisualizer> getVisualiser() {
		return visualiser;
	}

	void die() {
		shouldDie = true;
		t->join();
	}
};

#endif /* VISUALISER_H_ */
