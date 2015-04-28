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
		if(neuronType[cell.coordinates.GetX()][cell.coordinates.GetY()] == NOTHING) {
			// Case field is clear
            fillField(cell.coordinates.GetX(), cell.coordinates.GetY(), cell.cellType, cell.NeuronId);
		} else {
			// Case we need to create a new connection
			Neuron* source      = getNeuronById(cell.NeuronId);
			Neuron* destination = getNeuronById(neuronIds[cell.coordinates.GetX()][cell.coordinates.GetY()]);
			source->addConnection(cell.growthConeId, destination);
#ifdef CONNECTIONTRACES
			TRACE("hippocampus", "Added new connection between neuron %d and neuron %d", source->getNeuronId(), destination->getNeuronId());
#endif
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

void Hippocampus::tick() {
	ENTER_FUNCTION("hippocampus", "Hippocampus tick", "");
	if (numberOfNeurons == 0) {
		addNeuron(NUMBEROFCELLSX/2, NUMBEROFCELLSY/2);
		/*addNeuron(NUMBEROFCELLSX/2 - 50, NUMBEROFCELLSY/2);
		addNeuron(NUMBEROFCELLSX/2 + 50, NUMBEROFCELLSY/2);*/
		for (int i = 0; i < MAXNUMBEROFNEURONS; i++) {
			addNeuron();
		}
	}
	for(int i = 0; i < numberOfNeurons; i++)
		neurons[i].tick();
	checkStack();
	//if(numberOfNeurons == 0) {addNeuron(2, 5); addNeuron(2, 15); addNeuron(2, 25); addNeuron(7, 25); addNeuron(3, 25);}
};

int Hippocampus::getFieldType(int x, int y) {
	return neuronType[x][y];
};