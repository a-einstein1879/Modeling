#ifndef NEURITE_H
#define NEURITE_H

#include "cellStack.h"
#include "growthCone.h"
#include "coordinates.h"

class Neurite {
protected:
	//Axon, dendrite
	int type;
	int numberOfGrowthCones;
	GrowthCone *growthCones;
	Coordinates coordinates;
	int NeuronId;

	virtual int solveEquation(int growthConeId) = 0;
	virtual void growNeurite(int growthConeId, int delta) = 0;
public:
	Neurite();
	void setCoordinates(Coordinates coord);
	void setNeuronId(int newId);
	void tick();
};

class Axon : public Neurite {
private:
	int solveEquation(int growthConeId);
	void growNeurite(int growthConeId, int delta);
};

class Dendrite : public Neurite {
private:
	int solveEquation(int growthConeId);
	void growNeurite(int growthConeId, int delta);
};

#endif