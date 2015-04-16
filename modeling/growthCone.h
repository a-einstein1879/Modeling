#ifndef GROWTHCONE_H
#define GROWTHCONE_H

#include "cmn_struct.h"
#include "coordinates.h"
#include "environment.h"

class GrowthCone {
private:
	Coordinates coordinates;
	double somaDistance;
	bool growthEnabled;

	int neuronType;

	int centrifugalOrder;
	double previousLevelLength;
	
	void increaseSomaDistance(double delta);
public:
	GrowthCone();
	void setCoordinates(Coordinates coord); // use it only to set coordinates after creation
	void setNeuronType(int Type);           // use it only to set NeuronType  after creation
	void tick();

	void disableGrowth();
	bool isGrowthEnabled();
	void move(Coordinates coord, double delta);

	void increaseCentrifugalOrder();

	// interface
	GrowthCone& operator=(GrowthCone &growthCone);
	double getSomaDistance();
	double getPreviousLevelLength();
	Coordinates getCoordinates();
	int getCentrifugalOrder();
	int getNeuronType();
	void printStats();
};

#endif