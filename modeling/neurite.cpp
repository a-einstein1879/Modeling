#include "neurite.h"
#include "environment.h"
#include "cmn_defines.h"

Neurite::Neurite() {
	numberOfGrowthCones = 1;
	growthCones = new GrowthCone[numberOfGrowthCones];
};

void Neurite::setCoordinates(Coordinates coord) {
	coordinates = coord;
	//TODO:Growth cone coordinates shouldn`t be set here. Think where to move initialisation
	growthCones[0].setCoordinates(coordinates);
};

void Neurite::setNeuronId(int newId) {
	NeuronId = newId;
};

void Neurite::tick() {
	int delta;
	TRACE("neurite", "Neurite of neuron with id %d tick\n", NeuronId);
	for(int i = 0; i < numberOfGrowthCones; i++)
		if ( ( delta = solveEquation(i) ) > 0) {
			growNeurite(i, delta);
		}
};

int Axon::solveEquation(int growthConeId) {
	return 2;
};

void Axon::growNeurite(int growthConeId, int delta) {
	if(growthCones[growthConeId].isGrowthEnabled()) {
		Coordinates oldCoordinates = growthCones[growthConeId].getCoordinates();

		//get direction from environment
		struct Direction direction;
		Environment *environment = environment->getEnvironment();
		direction = environment->getDirection(oldCoordinates);

		Coordinates newCoordinates;
		newCoordinates.findNewCoordinates(oldCoordinates, delta, direction, AXON, NeuronId);
		growthCones[growthConeId].move(newCoordinates, delta);
	}
};

int Dendrite::solveEquation(int growthConeId) {
	return 1;
};

void Dendrite::growNeurite(int growthConeId, int delta) {};