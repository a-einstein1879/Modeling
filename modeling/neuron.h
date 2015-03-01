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

	int numberOfConnections;
	struct Connection {
		Neuron *neuron;
		int delay;
		//double probability;
	}*connections;
public:
	static int NeuronCounter;
	void resetIdCounter();

	Neuron();
	~Neuron();
	void setCoordinates(int x, int y);
	void setCoordinates(Coordinates tmpCoord);

	int addAxon(Coordinates coordinates);
	int addConnection(int growthConeId, Neuron* neuron);

	int getNeuronId();

	void tick();
};

#endif