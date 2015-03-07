#include "neurite.h"
#include "environment.h"
#include "cmn_defines.h"

Neurite::Neurite() {
	numberOfGrowthCones = 0;
	addGrowthCone();
};

void Neurite::addGrowthCone(int growthConeId) {
	GrowthCone *tmpGrowthCones;
	tmpGrowthCones = new GrowthCone[numberOfGrowthCones];
	for(int i = 0; i < numberOfGrowthCones; i++) {
		tmpGrowthCones[i] = growthCones[i];
	}

	growthCones = new GrowthCone[++numberOfGrowthCones];

	for(int i = 0; i < numberOfGrowthCones - 1; i++) {
		growthCones[i] = tmpGrowthCones[i];
	}

	delete [] tmpGrowthCones;

	if (growthConeId != -1) {
		growthCones[numberOfGrowthCones - 1] = growthCones[growthConeId];
	}
	else {
		growthCones[numberOfGrowthCones - 1].setCoordinates(coordinates);
	}
};

void Neurite::setCoordinates(Coordinates coord) {
	coordinates = coord;
	//TODO:Growth cone coordinates shouldn`t be set here. Think where to move initialisation
	growthCones[0].setCoordinates(coordinates);
};

void Neurite::setNeuronId(int newId) {
	NeuronId = newId;
};

void Neurite::setType(int Type) {
	type = Type;
};

int Neurite::getGrowthConeDistance(int growthConeId) {
	return growthCones[growthConeId].getSomaDistance();
};

void Neurite::growNeurite(int growthConeId, double delta, bool branching) {
	if(growthCones[growthConeId].isGrowthEnabled()) {
		Coordinates oldCoordinates = growthCones[growthConeId].getCoordinates();

		//get direction from environment
		struct Direction direction;
		Environment *environment = environment->getEnvironment();
		direction = environment->getDirection(oldCoordinates);

		if (branching == true) {
			struct Direction twoDirections[2];
			getTwoDirections(direction, twoDirections);
			TRACE("neurite", "It`s time to branch now for neuron with neuron id %d and growth cone id %d\n", NeuronId, growthConeId);
			addGrowthCone(growthConeId);

			growGrowthCone(oldCoordinates, delta, twoDirections[0], type, NeuronId, numberOfGrowthCones - 1);

			growGrowthCone(oldCoordinates, delta, twoDirections[1], type, NeuronId, growthConeId);
		}
		else {
			TRACE("neurite", "Growth cone %d with neuron id %d grows\n", growthConeId, NeuronId);
			//TRACE("neurite", "Growth cone %d with neuron id %d grows\nfi = %e; delta = %e\n", growthConeId, NeuronId, direction.fi, delta);
			growGrowthCone(oldCoordinates, delta, direction, type, NeuronId, growthConeId);
		}
	}
};

void Neurite::growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId) {
		Coordinates newCoordinates;
		double realDelta = newCoordinates.findNewCoordinates(coord, delta, direction, type, NeuronId, growthConeId);
		growthCones[growthConeId].move(newCoordinates, realDelta);
		if (realDelta == -1) {
			growthCones[growthConeId].disableGrowth();
			TRACE("neurite", "Growth cone growth is now disabled. Coordinates:\n", growthConeId, NeuronId);
			growthCones[growthConeId].getCoordinates().PrintCoordinates();
		}
};

void Neurite::tick() {
	double delta;
	int numberOfGrowthConesBeforeTick = numberOfGrowthCones;
	TRACE("neurite", "Neurite of neuron with id %d tick\n", NeuronId);
	for(int i = 0; i < numberOfGrowthConesBeforeTick; i++)
		if ( ( delta = solveEquation(i) ) > 0) {
			growNeurite(i, delta, solveEmbranchmentEquation());
		}
};

double Axon::solveEquation(int growthConeId) {
	TRACE("neurite", "Solving equation of neuron with id %d and growth cone id %d\n", NeuronId, growthConeId);
	return 5;
};

bool Axon::solveEmbranchmentEquation() {
	TRACE("neurite", "Soma distance is %d\n", getGrowthConeDistance(0));
	if ( (getGrowthConeDistance(0) >= 3) && (getGrowthConeDistance(0) <= 4) ||
		 (getGrowthConeDistance(0) >= 6) && (getGrowthConeDistance(0) <= 7)) {
		return true;
	} else {
		return false;
	}
};

double Dendrite::solveEquation(int growthConeId) {
	return 1;
};

bool Dendrite::solveEmbranchmentEquation() {
	return true;
};