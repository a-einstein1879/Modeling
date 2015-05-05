#include "neuron.h"
#include "cmn_defines.h"

int Neuron::NeuronCounter = 0;

void Neuron::resetIdCounter() {
   NeuronCounter = 0;
};

/* For random */
#include <cstdlib>
Neuron::Neuron() {
	ENTER_FUNCTION("neuron", "Neuron::Neuron()", "");
	if (NeuronCounter < MAXNUMBEROFNEURONS) {
		NeuronId = NeuronCounter++;
	};
	neuronType = rand()%NUMBEROFNEURONTYPES;

	numberOfAxons = 0;
	axons = new Axon[numberOfAxons];

	numberOfDendrites = 0;
	dendrites = new Dendrite[numberOfDendrites];

	numberOfConnections = 0;
	connections = new Connection[numberOfConnections];

	TRACE("neuron", "Neuron with id %d was created", NeuronId);
};

Neuron::~Neuron() {
	NeuronCounter--;
	delete [] axons;
	delete [] dendrites;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
	ENTER_FUNCTION("neuron", "setCoordinates(int x, int y)", "x = %d, y = %d", x, y);
	coord.SetX(x);
	coord.SetY(y);

	TRACE("neuron", "Coordinates of neuron number %d were changed. New coordinates are:", NeuronId);
	coord.PrintCoordinates();
}

void Neuron::setCoordinates(Coordinates tmpCoord) {//TODO: proper checking of coordinates availability
	ENTER_FUNCTION("neuron", "setCoordinates(Coordinates tmpCoord)", "");
    coord = tmpCoord;

	TRACE("neuron", "Coordinates of neuron number %d were changed. New coordinates are:", NeuronId);
	coord.PrintCoordinates();
}

int Neuron::addAxon(Coordinates coordinates) {
	ENTER_FUNCTION("neuron", "addAxon(Coordinates coordinates)", "");
	dynamicArrayRealloc(Axon, axons, numberOfAxons);

	axons[numberOfAxons - 1].setType(AXON);
	axons[numberOfAxons - 1].setNeuronId(NeuronId);
	axons[numberOfAxons - 1].setNeuronType(neuronType);
	axons[numberOfAxons - 1].setCoordinates(coordinates);
	
	TRACE("neuron", "Neuron id %d now has new axon. The number of axons: %d", NeuronId, numberOfAxons);
	return 0;
};

int Neuron::addDendrite(Coordinates coordinates) {
	ENTER_FUNCTION("neuron", "addDendrite(Coordinates coordinates)", "");
	dynamicArrayRealloc(Dendrite, dendrites, numberOfDendrites);

	dendrites[numberOfDendrites - 1].setType(DENDRITE);
	dendrites[numberOfDendrites - 1].setNeuronId(NeuronId);
	dendrites[numberOfDendrites - 1].setNeuronType(neuronType);
	dendrites[numberOfDendrites - 1].setCoordinates(coordinates);
	
	TRACE("neuron", "Neuron id %d now has new dendrite. The number of dendrites: %d", NeuronId, numberOfDendrites);
	return 0;
};

int Neuron::addConnection(int growthConeId, Neuron* neuron) {
	ENTER_FUNCTION("neuron", "addConnection(int growthConeId, Neuron* neuron)", "Source: neuronId = %d, Destination: neuronId = %d; growthConeId = %d", NeuronId, neuron->getNeuronId(), growthConeId);
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

	connections[numberOfConnections - 1].delay  = (int)axons[0].getGrowthConeDistance(growthConeId);;
		//(int)axons->getGrowthConeDistance(growthConeId);
	
#ifdef CONNECTIONTRACES
	TRACE("neuron", "Neuron id %d now has new connection with delay %d. The number of connections: %d", NeuronId, connections[numberOfConnections - 1].delay, numberOfConnections);
#endif
	return 0;
};

void Neuron::tick() {
	ENTER_FUNCTION("neuron", "Neuron::tick()", "NeuronId = %d", NeuronId);
	Environment *environment;
	environment = environment->getEnvironment();
	environment->addSource(coord, neuronType);

#ifdef AXONGROWTH
	if(numberOfAxons != 0) {
		for(int i = 0; i < numberOfAxons; i++)
			axons[i].tick();
	} else { 
		addAxon(coord);
	}
#endif

#ifdef DENDRITEGROWTH
	if(numberOfDendrites != 0) {
		for(int i = 0; i < numberOfDendrites; i++)
			dendrites[i].tick();
	} else {
		addDendrite(coord);
	}
#endif
};

Neuron& Neuron::operator=(Neuron &neuron) {
	NeuronId          = neuron.getNeuronId();
	coord             = neuron.getCoordinates();
	neuronType        = neuron.getNeuronType();

	numberOfAxons     = neuron.getNumberOfAxons();
	/*for(int i = 0; i < numberOfAxons; i++)
		axons[i]      = neuron.getAxon(i);

	numberOfDendrites = neuron.getNumberOfDendrites();
	for(int i = 0; i < numberOfDendrites; i++)
		dendrites[i]  = neuron.getDendrite(i);*/

	numberOfConnections = neuron.getNumberOfConnections();
/*	for(int i = 0; i < numberOfConnections; i++) {
		connections[i].neuron = neuron.getConnection(i).neuron;
		connections[i].delay  = neuron.getConnection(i).delay;
	}*/
	return *this;
};

int Neuron::getNeuronId() {
	return NeuronId;
};

Coordinates Neuron::getCoordinates() {
	return coord;
};

int Neuron::getNeuronType() {
	return neuronType;
};

int Neuron::getNumberOfAxons() {
	return numberOfAxons;
};

int Neuron::getNumberOfDendrites() {
	return numberOfDendrites;
};

Axon Neuron::getAxon(int neuriteId) {
	return axons[neuriteId];
};

Dendrite Neuron::getDendrite(int neuriteId) {
	return dendrites[neuriteId];
};

int Neuron::getNumberOfConnections() {
	return numberOfConnections;
};

/*struct Connection Neuron::getConnection(int connectionId) {
	return connections[connectionId];
};*/