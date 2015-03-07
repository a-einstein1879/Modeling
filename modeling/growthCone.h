#ifndef GROWTHCONE_H
#define GROWTHCONE_H

#include "cmn_struct.h"
#include "coordinates.h"

class GrowthCone {
private:
	double somaDistance;
	void increaseSomaDistance(double delta);
	bool growthEnabled;
	Coordinates coordinates;
public:
	GrowthCone& operator=( GrowthCone &growthCone );
	GrowthCone();
	void disableGrowth();
	bool isGrowthEnabled();
	void move(Coordinates coord, double delta);
	double getSomaDistance();
	void setCoordinates(Coordinates coord); // use it only to set coordinates after creation
	Coordinates getCoordinates();
	void printStats();
};

#endif