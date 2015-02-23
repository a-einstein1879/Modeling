#ifndef NEURON_H
#define NEURON_H

#include "cmn_struct.h"
#include "neurite.h"

class Neuron {
private:
	int NeuronId;
	Coordinates coord;

	int numberOfAxons;
	Axon *axons;
public:
	static int NeuronCounter;
	void resetIdCounter();

	Neuron();
	~Neuron();
	void setCoordinates(int x, int y);
	void setCoordinates(Coordinates tmpCoord);

	int addAxon(Coordinates coordinates);

	void tick();
};

#endif