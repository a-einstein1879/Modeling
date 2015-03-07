#include "neuron.h"
#include "cmn_defines.h"

int Neuron::NeuronCounter = 0;

void Neuron::resetIdCounter() {
   NeuronCounter = 0;
};

Neuron::Neuron() {
	if (NeuronCounter < MAXNUMBEROFNEURONS) {
		NeuronId = NeuronCounter++;
	};

	numberOfAxons = 0;
	axons = new Axon[numberOfAxons];

	numberOfConnections = 0;
	connections = new Connection[numberOfConnections];

	TRACE("neuron", "Neuron with id %d was created\n", NeuronId);
};

Neuron::~Neuron() {
	NeuronCounter--;
	delete [] axons;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
	coord.SetX(x);
	coord.SetY(y);

	TRACE("neuron", "Coordinates of neuron number %d were changed. New coordinates are:\n", NeuronId);
	coord.PrintCoordinates();
}

void Neuron::setCoordinates(Coordinates tmpCoord) {//TODO: proper checking of coordinates availability
    coord = tmpCoord;

	TRACE("neuron", "Coordinates of neuron number %d were changed. New coordinates are:\n", NeuronId);
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
	axons[numberOfAxons - 1].setType(AXON);
	
	TRACE("neuron", "Neuron id %d now has new axon. The number of axons: %d\n", NeuronId, numberOfAxons);
	return 0;
};

int Neuron::addConnection(int growthConeId, Neuron* neuron) {
	Connection *tmpConnections;
	tmpConnections = new Connection[numberOfConnections];
	for(int i = 0; i < numberOfConnections; i++) {
		tmpConnections[i].neuron = connections[i].neuron;
		tmpConnections[i].delay  = connections[i].delay;
	}

	connections = new Connection[++numberOfConnections];

	for(int i = 0; i < numberOfConnections - 1; i++) {
		connections[i].neuron = tmpConnections[i].neuron;
		connections[i].delay  = tmpConnections[i].delay;
	}

	delete [] tmpConnections;

	connections[numberOfConnections - 1].neuron = neuron;
	connections[numberOfConnections - 1].delay  = axons->getGrowthConeDistance(growthConeId);
	
#ifdef CONNECTIONTRACES
	TRACE("neuron", "Neuron id %d now has new connection with delay %d. The number of connections: %d\n", NeuronId, connections[numberOfConnections - 1].delay,numberOfConnections);
#endif
	return 0;
};

int Neuron::getNeuronId() {
	return NeuronId;
};

void Neuron::tick() {
	TRACE("neuron", "Neuron with id %d tick\n", NeuronId);
	if(numberOfAxons == 0) {addAxon(coord);}
	for(int i = 0; i <numberOfAxons; i++)
		axons[i].tick();
};