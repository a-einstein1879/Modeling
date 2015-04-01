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
	virtual bool solveEmbranchmentEquation(int growthConeId) = 0;
public:
	Neurite();

	void setCoordinates(Coordinates coord);	//Should be used right after creation and nowhere else
	void setNeuronId(int newId);
	void setType(int Type);

	double getGrowthConeDistance(int growthConeId);
	void tick();
};

class Axon : public Neurite {
private:
	double solveEquation(int growthConeId);
	bool solveEmbranchmentEquation(int growthConeId);
};

class Dendrite : public Neurite {
private:
	double solveEquation(int growthConeId);
	bool solveEmbranchmentEquation(int growthConeId);
};

#endif