#ifndef HIPPOCAMPUS_H
#define HIPPOCAMPUS_H

#include "neuron.h"
#include "cmn_defines.h"
#include "cmn_struct.h"

class Hippocampus {
private:
	int numberOfNeurons;
	Neuron *neurons;
	int neuronType[NUMBEROFCELLSX][NUMBEROFCELLSY];
	int neuronIds[NUMBEROFCELLSX][NUMBEROFCELLSY];

	void checkStack();
	int  addNeuron(int x = -1, int y = -1);
	void fillField(int x, int y, char type, int neuronId);
	void createNeuron();
	Neuron* getNeuronById(int neuronId);
public:
	Hippocampus();
	int getFieldType(int x, int y);
	void printConnectivityGraphStatistics();
	void tick(int t);
};

#endif