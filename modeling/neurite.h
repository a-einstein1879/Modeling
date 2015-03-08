#ifndef NEURITE_H
#define NEURITE_H

#include "cellStack.h"
#include "growthCone.h"
#include "coordinates.h"

class Neurite {
protected:
	//Axon AXON, dendrite DENDRITE
	int type;

	int numberOfGrowthCones;
	GrowthCone *growthCones;
	void addGrowthCone(int growthConeId = -1);

	Coordinates coordinates;
	int NeuronId;

	void growNeurite(int growthConeId, double delta, bool branching);
	void growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId);

	virtual double solveEquation(int growthConeId) = 0;
	virtual bool solveEmbranchmentEquation() = 0;
public:
	Neurite();

	//Should only be used right after creation
	void setCoordinates(Coordinates coord);
	void setNeuronId(int newId);
	void setType(int Type);

	int getGrowthConeDistance(int growthConeId);
	void tick();
};

class Axon : public Neurite {
private:
	double solveEquation(int growthConeId);
	bool solveEmbranchmentEquation();
};

class Dendrite : public Neurite {
private:
	double solveEquation(int growthConeId);
	bool solveEmbranchmentEquation();
};

#endif