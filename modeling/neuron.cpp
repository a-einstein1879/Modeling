#include "neuron.h"
#include "cmn_defines.h"

int Neuron::NeuronCounter = 0;

void Neuron::resetIdCounter() {
   NeuronCounter = 0;
}

Neuron::Neuron() {
	if (NeuronCounter < MAXNUMBEROFNEURONS) {
		NeuronId = NeuronCounter++;
	};
	TRACE("Neuron", "Neuron with id %d was created\n", NeuronId);
};

Neuron::~Neuron() {
	NeuronCounter--;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
	coord.SetX(x);
	coord.SetY(y);

	TRACE("Neuron", "Coordinates of neuron number %d were changed. New coordinates are:\n");
	coord.PrintCoordinates();
}

void Neuron::setCoordinates(Coordinates tmpCoord) {//TODO: proper checking of coordinates availability
    coord = tmpCoord;

	TRACE("Neuron", "Coordinates of neuron number %d were changed. New coordinates are:\n");
	coord.PrintCoordinates();
}

void Neuron::tick() {
	TRACE("Neuron", "Neuron with id %d tick\n", NeuronId);
};