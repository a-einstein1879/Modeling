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

	numberOfDendrites = 0;
	dendrites = new Dendrite[numberOfDendrites];

	numberOfConnections = 0;
	connections = new Connection[numberOfConnections];

	TRACE("neuron", "Neuron with id %d was created\n", NeuronId);
};

Neuron::~Neuron() {
	NeuronCounter--;
	delete [] axons;
	delete [] dendrites;
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
	dynamicArrayRealloc(Axon, axons, numberOfAxons);

	axons[numberOfAxons - 1].setCoordinates(coordinates);
	axons[numberOfAxons - 1].setNeuronId(NeuronId);
	axons[numberOfAxons - 1].setType(AXON);
	
	TRACE("neuron", "Neuron id %d now has new axon. The number of axons: %d\n", NeuronId, numberOfAxons);
	return 0;
};

int Neuron::addDendrite(Coordinates coordinates) {
	dynamicArrayRealloc(Dendrite, dendrites, numberOfDendrites);

	dendrites[numberOfDendrites - 1].setCoordinates(coordinates);
	dendrites[numberOfDendrites - 1].setNeuronId(NeuronId);
	dendrites[numberOfDendrites - 1].setType(DENDRITE);
	
	TRACE("neuron", "Neuron id %d now has new dendrite. The number of dendrites: %d\n", NeuronId, numberOfDendrites);
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
	connections[numberOfConnections - 1].delay  = (int)axons->getGrowthConeDistance(growthConeId);
	
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
	if(numberOfAxons     == 0 && NeuronId == 0) {addAxon(coord);}
	if(numberOfDendrites == 0 && NeuronId == 1) {addDendrite(coord);}

	for(int i = 0; i <numberOfAxons; i++)
		axons[i].tick();

	for(int i = 0; i <numberOfDendrites; i++)
		dendrites[i].tick();
};