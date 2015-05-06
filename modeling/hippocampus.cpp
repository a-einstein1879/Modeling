#include "hippocampus.h"
#include "neuron.h"

/* For random */
#include <cstdlib>

Hippocampus::Hippocampus() {
	numberOfNeurons = 0;

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			neuronType[i][j] = NOTHING;

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			neuronIds[i][j] = 0;
};

#include "cellStack.h"
void Hippocampus::checkStack() {
	ENTER_FUNCTION("hippocampus", "checkStack()", "", );
	CellStack *cellStack = cellStack->getStack();
	while(!cellStack->isEmpty()) {
		Cell cell = cellStack->stackPull();
		int x = cell.coordinates.GetX();
		int y = cell.coordinates.GetY();
		switch(neuronType[x][y])
		{
		case NOTHING:
			// Case field is clear
            fillField(x, y, cell.cellType, cell.NeuronId);
			break;
		case DENDRITE:
			// Case we need to create a new connection
			// Axon can be connected to dendrite
			if(cell.NeuronId != neuronIds[x][y] && cell.cellType == AXON) {
				Neuron* source      = getNeuronById(cell.NeuronId);
				Neuron* destination = getNeuronById(neuronIds[x][y]);
				source->addConnection(cell.growthConeId, destination, cell.somaDistance);
#ifdef CONNECTIONTRACES
				TRACE("hippocampus", "Added new connection between neuron %d and neuron %d", source->getNeuronId(), destination->getNeuronId());
#endif
			}
			break;
		case AXON:
			// Case we need to create a new connection
			// Dendrite can be connected to axon
			if(cell.NeuronId != neuronIds[x][y] && cell.cellType == DENDRITE) {
				Neuron* source      = getNeuronById(cell.NeuronId);
				Neuron* destination = getNeuronById(neuronIds[x][y]);
				source->addConnection(cell.growthConeId, destination, cell.somaDistance);
#ifdef CONNECTIONTRACES
				TRACE("hippocampus", "Added new connection between neuron %d and neuron %d", source->getNeuronId(), destination->getNeuronId());
#endif
			}
			break;
		}
	}
};

int Hippocampus::addNeuron(int x, int y) {
	ENTER_FUNCTION("hippocampus", "addNeuron(int x, int y)", "x = %d, y = %d", x, y);
	//TODO: fix recursive bug. Add counter to prevent loop
	//TODO: use cell stack to add neuron
	if (numberOfNeurons < MAXNUMBEROFNEURONS) {
		bool availability = false, randomity = false;
		if ((x == -1) && (y == -1)) {x = rand()%(NUMBEROFCELLSX - 2) + 1; y = rand()%(NUMBEROFCELLSY - 2) + 1; randomity = true;}
		if (getFieldType(x, y) == NOTHING) {availability = true;}

		if (availability == true) {
			createNeuron();
            neurons[numberOfNeurons - 1].setCoordinates(x, y);
            fillField(x, y, NEURON, numberOfNeurons - 1);
		}
		else {
			if (randomity == true)
				addNeuron();
			else {
				TRACE("hippocampus", "Can`t create neuron here (%d, %d)", x, y);
			}
		}
	}
	return 0;
}

void Hippocampus::fillField(int x, int y, char type, int neuronId) {
	ENTER_FUNCTION("hippocampus", "fillField(int x, int y, char type, int neuronId)", "x = %d, y = %d, type = %d, neuronId = %d", x, y, type, neuronId);
	neuronType[x][y] = type;
	neuronIds[x][y]  = neuronId;

	TRACE("hippocampus", "Space (%d, %d) is now `%d` type with id %d", x, y, getFieldType(x, y), neuronIds[x][y]);
}

void Hippocampus::createNeuron() {
	ENTER_FUNCTION("hippocampus", "createNeuron", "numberOfNeurons = %d", numberOfNeurons);
	if (numberOfNeurons < MAXNUMBEROFNEURONS) {
		Neuron *tmpNeurons;
		neurons->resetIdCounter();
		tmpNeurons = new Neuron[numberOfNeurons];
		for(int i = 0; i < numberOfNeurons; i++)
			tmpNeurons[i] = neurons[i];

		neurons->resetIdCounter();
		neurons = new Neuron[++numberOfNeurons];

		for(int i = 0; i < numberOfNeurons - 1; i++)
			neurons[i] = tmpNeurons[i];

		delete [] tmpNeurons;
	}
	TRACE("hippocampus", "Hippocampus now has %d neurons", numberOfNeurons);
};

Neuron* Hippocampus::getNeuronById(int neuronId) {
	Neuron* neuron = NULL;
	for(int i = 0; i < numberOfNeurons; i++) {
		if (neurons[i].getNeuronId() == neuronId) {
			neuron = neurons + i;
			break;
		}
	};
	return neuron;
};

/************************/
/*      Interface       */
/************************/

void Hippocampus::tick(int t) {
	ENTER_FUNCTION("hippocampus", "Hippocampus tick", "");
	if (numberOfNeurons == 0) {
		//addNeuron(NUMBEROFCELLSX/2, NUMBEROFCELLSY/2);
#ifdef CONNECTIVITYTEST1
		addNeuron(NUMBEROFCELLSX/2 - 50, NUMBEROFCELLSY/2);
		addNeuron(NUMBEROFCELLSX/2 + 50, NUMBEROFCELLSY/2);
#endif
		for (int i = 0; i < MAXNUMBEROFNEURONS; i++) {
			addNeuron();
		}
	}
	for(int i = 0; i < numberOfNeurons; i++)
		neurons[i].tick();
	checkStack();
	if( (t % CONNECTIVITYGRAPHSTATISTICSRATE) == 1 ) {printConnectivityGraphStatistics();}
	//if(numberOfNeurons == 0) {addNeuron(2, 5); addNeuron(2, 15); addNeuron(2, 25); addNeuron(7, 25); addNeuron(3, 25);}
};

void Hippocampus::printConnectivityGraphStatistics() {
	ENTER_FUNCTION("hippocampus", "printConnectivityGraphStatistics()", "");
	int *numberOfConnections;
	int totalNumberOfConnections = 0;
	struct Connections {
		int sourceId;
		int destinationId;
		int delay;
	};
	if(numberOfNeurons != 0) {
		numberOfConnections = new int[numberOfNeurons];

		for(int i = 0; i < numberOfNeurons; i++) {
			numberOfConnections[i] = neurons[i].getNumberOfConnections();
			totalNumberOfConnections += numberOfConnections[i];
		}
		CONNECTIVITYGRAPHSTATISTIC("Number of connections:");

		for(int i = 0; i < numberOfNeurons; i++) {
			CONNECTIVITYGRAPHSTATISTIC("%d\t%d", i, numberOfConnections[i])
		}
		struct Connections *connections;
		connections = new struct Connections[totalNumberOfConnections];

		int counter = 0;
		for(int i = 0; i < numberOfNeurons; i++) {
			for(int j = 0; j < numberOfConnections[i]; j++) {
				connections[counter].sourceId      = i;
				connections[counter].destinationId = neurons[i].getConnectionDestination(j);
				connections[counter].delay         = neurons[i].getConnectionDelay(j);
				counter++;
			}
		}

		CONNECTIVITYGRAPHSTATISTIC("Source\tDest\tDelay");
		for(int i = 0; i < totalNumberOfConnections; i++) {
			CONNECTIVITYGRAPHSTATISTIC("%d\t%d\t%d", connections[i].sourceId, connections[i].destinationId, connections[i].delay);
		}

		delete [] connections;
		delete [] numberOfConnections;
	}
};

int Hippocampus::getFieldType(int x, int y) {
	return neuronType[x][y];
};