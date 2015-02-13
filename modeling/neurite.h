#ifndef NEURITE_H
#define NEURITE_H

#include "cellStack.h"

class Neurite {
protected:
	//Axon, dendrite
	int type;
	int numberOfGrowthCones;
	int length;
	bool growthEnabled;

	virtual void solveEquation() = 0;
	virtual void growNeurite() = 0;
public:
	void tick();
};

class Axon : public Neurite {
	void solveEquation();
	void growNeurite();
};

class Dendrite : public Neurite {
	void solveEquation();
	void growNeurite();
};

#endif