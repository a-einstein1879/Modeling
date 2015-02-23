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
	numberOfAxons = 0;
	axons = new Axon[numberOfAxons];
	TRACE("Neuron", "Neuron with id %d was created\n", NeuronId);
};

Neuron::~Neuron() {
	NeuronCounter--;
	delete [] axons;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
	coord.SetX(x);
	coord.SetY(y);

	TRACE("Neuron", "Coordinates of neuron number %d were changed. New coordinates are:\n", NeuronId);
	coord.PrintCoordinates();
}

void Neuron::setCoordinates(Coordinates tmpCoord) {//TODO: proper checking of coordinates availability
    coord = tmpCoord;

	TRACE("Neuron", "Coordinates of neuron number %d were changed. New coordinates are:\n", NeuronId);
	coord.PrintCoordinates();
}

int Neuron::addAxon(Coordinates coordinates) {
	Axon *tmpAxons;
	tmpAxons = new Axon[numberOfAxons];
	for(int i = 0; i < numberOfAxons; i++)
		*(tmpAxons+i) = axons[i];

	axons = new Axon[++numberOfAxons];

	for(int i = 0; i < numberOfAxons - 1; i++)
		axons[i] = *(tmpAxons+i);

	delete [] tmpAxons;
	axons[numberOfAxons - 1].setCoordinates(coordinates);
	axons[numberOfAxons - 1].setNeuronId(NeuronId);
	
	TRACE("Neuron", "Neuron id %d now has new axon. The number of axons: \n", NeuronId, numberOfAxons);
	return 0;
};

void Neuron::tick() {
	TRACE("Neuron", "Neuron with id %d tick\n", NeuronId);
	if(numberOfAxons == 0) {addAxon(coord);}
	for(int i = 0; i <numberOfAxons; i++)
		axons[i].tick();
};