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

	/* Coefficients below and formulas for growth are taken from Mironov, Semyanov, Kazantsev "Dendrite and axon specific geometrical adaptation in neurite development" */
	double alpha;
	double betta;
	double c0;
	double T;
	double Vat;
	double k;
	void growNeurite(int growthConeId, double delta, bool branching);
	void growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId);

	virtual double solveEquation(int growthConeId) = 0;
	virtual bool solveEmbranchmentEquation(int growthConeId) = 0;
public:
	Neurite();

	//Should only be used right after creation
	void setCoordinates(Coordinates coord);
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