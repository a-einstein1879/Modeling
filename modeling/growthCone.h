#ifndef GROWTHCONE_H
#define GROWTHCONE_H

#include "cmn_struct.h"
#include "coordinates.h"
#include "environment.h"

class GrowthCone {
private:
	int centrifugalOrder;
	double somaDistance;
	void increaseSomaDistance(double delta);
	bool growthEnabled;
	Coordinates coordinates;
public:
	GrowthCone();
	void setCoordinates(Coordinates coord); // use it only to set coordinates after creation

	void disableGrowth();
	bool isGrowthEnabled();
	void move(Coordinates coord, double delta);

	void increaseCentrifugalOrder();

	// interface
	GrowthCone& operator=(GrowthCone &growthCone);
	double getSomaDistance();
	Coordinates getCoordinates();
	int getCentrifugalOrder();
	void printStats();
};

#endif