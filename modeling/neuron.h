#ifndef NEURON_H
#define NEURON_H

#include "cmn_struct.h"
class Neuron {
private:
	int NeuronId;
	Coordinates coord;
public:
	static int NeuronCounter;
	void resetIdCounter();

	Neuron();
	~Neuron();
	void setCoordinates(int x, int y);
	void setCoordinates(Coordinates tmpCoord);

	void tick();
};

#endif