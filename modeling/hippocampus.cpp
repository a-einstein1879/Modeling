#include "hippocampus.h"
#include "neuron.h"

/* For random */
#include <cstdlib>
#include <ctime>

Hippocampus::Hippocampus() {
	numberOfNeurons = 0;

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			neuronType[i][j] = NOTHING;

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			neuronIds[i][j] = 0;
};

int Hippocampus::addNeuron(int x, int y) { //TODO: fix recursive bug. Add counter to prevent loop
   if (numberOfNeurons < MAXNUMBEROFNEURONS) {
      bool availability = false, randomity = false;
      if ((x == -1) && (y == -1)) {x = rand()%NUMBEROFCELLSX; y = rand()%NUMBEROFCELLSY; randomity = true;}
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
            TRACE("Hippocampus", "Can`t create neuron here (%d, %d)\n", x, y);
         }
      }
   }
   return 0;
}

void Hippocampus::fillField(int x, int y, char type, int neuronId) {
   neuronType[x][y] = type;
   neuronIds[x][y]  = neuronId;

   TRACE("Hippocampus", "Space (%d, %d) is now `%d` type with id %d\n", x, y, getFieldType(x, y), neuronIds[x][y]);
}

void Hippocampus::createNeuron() {
	if (numberOfNeurons < MAXNUMBEROFNEURONS) {
		Neuron *tmpNeurons;
		neurons->resetIdCounter();
		tmpNeurons = new Neuron[numberOfNeurons];
		for(int i = 0; i < numberOfNeurons; i++)
			*(tmpNeurons+i) = neurons[i];

		neurons->resetIdCounter();
		neurons = new Neuron[++numberOfNeurons];

		for(int i = 0; i < numberOfNeurons - 1; i++)
			neurons[i] = *(tmpNeurons+i);

		delete [] tmpNeurons;
	}
	TRACE("Hippocampus", "Hippocampus now has %d neurons\n", numberOfNeurons);
};

/************************/
/*      Interface       */
/************************/

void Hippocampus::tick() {
	TRACE("Hippocampus", "Hippocampus tick\n");
	for(int i = 0; i < numberOfNeurons; i++)
		neurons[i].tick();
	addNeuron(10, 10);
};

int Hippocampus::getFieldType(int x, int y) {
	return neuronType[x][y];
};