#include "neurite.h"
#include "environment.h"
#include "cmn_defines.h"

Neurite::Neurite() {
	numberOfGrowthCones = 0;
	addGrowthCone();
	
	alpha = 1.1;
	betta = 1.18;
	c0    = 14;
	T     = 0.005;
	Vat   = 40;
	k     = 0.00005;
};

void Neurite::addGrowthCone(int growthConeId) {
	ENTER_FUNCTION("neurite", "addGrowthCone(int growthConeId)", "growthConeId = %d", growthConeId);
	dynamicArrayRealloc(GrowthCone, growthCones, numberOfGrowthCones);
	
	if (growthConeId != -1) {
		growthCones[numberOfGrowthCones - 1] = growthCones[growthConeId];
		growthCones[growthConeId].printStats();
		growthCones[numberOfGrowthCones - 1].printStats();
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

double Neurite::getGrowthConeDistance(int growthConeId) {
	return growthCones[growthConeId].getSomaDistance();
};

void Neurite::growNeurite(int growthConeId, double delta, bool branching) {
	ENTER_FUNCTION("neurite", "growNeurite(int growthConeId, double delta, bool branching)", "growthConeId = %d, delta = %.2f, branching = %d", growthConeId, delta, branching);
	if(growthCones[growthConeId].isGrowthEnabled()) {
		Coordinates oldCoordinates = growthCones[growthConeId].getCoordinates();

		//get direction from environment
		struct Direction direction;
		Environment *environment = environment->getEnvironment();
		direction = environment->getDirection(oldCoordinates);

		if (branching == true) {
			struct Direction twoDirections[2];
			getTwoDirections(direction, twoDirections);
			TRACE("neurite", "It`s time to branch now for neuron with neuron id %d and growth cone id %d", NeuronId, growthConeId);
			addGrowthCone(growthConeId);

			growGrowthCone(oldCoordinates, delta, twoDirections[0], type, NeuronId, numberOfGrowthCones - 1);

			growGrowthCone(oldCoordinates, delta, twoDirections[1], type, NeuronId, growthConeId);
		}
		else {
			growGrowthCone(oldCoordinates, delta, direction, type, NeuronId, growthConeId);
		}
	}
};

void Neurite::growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId) {
	ENTER_FUNCTION("neurite", "growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId)",
		"delta = %.2f, direction.fi = %.2f, type = %d, NeuronId = %d, growthConeId = %d", delta, direction.fi, type, NeuronId, growthConeId);
	TRACE("neurite", "Growth cone %d with neuron id %d grows by %.2f", growthConeId, NeuronId, delta);
	Coordinates newCoordinates;
	double realDelta = newCoordinates.findNewCoordinates(coord, delta, direction, type, NeuronId, growthConeId);
	growthCones[growthConeId].move(newCoordinates, realDelta);
	if (realDelta == -1) {
		growthCones[growthConeId].disableGrowth();
		TRACE("neurite", "Growth cone growth is now disabled. Coordinates:", growthConeId, NeuronId);
		growthCones[growthConeId].getCoordinates().PrintCoordinates();
	}
};

void Neurite::tick() {
	ENTER_FUNCTION("neurite", "Neurite::tick()", "NeuronId = %d", NeuronId);
	double delta;
	int numberOfGrowthConesBeforeTick = numberOfGrowthCones;
	for(int i = 0; i < numberOfGrowthConesBeforeTick; i++)
		if ( ( delta = solveEquation(i) ) > 0) {
			growNeurite(i, delta, solveEmbranchmentEquation(i));
		}
};

#include <math.h>
double Axon::solveEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Axon::solveEquation(int growthConeId)", "growthConeId = %d", growthConeId);
	double delta;
	double length = getGrowthConeDistance(growthConeId);
	delta = alpha * c0 * exp ( ( k - T / Vat ) * length ) - betta;
	TRACE("neurite", "Solved axon equation of neuron with id %d and growth cone id %d. Delta = %.2f", NeuronId, growthConeId, delta);
	return delta;
};

/* For rand() */
#include <stdlib.h>
bool Axon::solveEmbranchmentEquation(int growthConeId) {
	//return (bool)rand();
	return false;
};

#include <math.h>
double Dendrite::solveEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Dendrite::solveEquation(int growthConeId)", "growthConeId = %d", growthConeId);
	double delta;
	double length = getGrowthConeDistance(growthConeId);
	delta = alpha * c0 * pow ( 1 + k * length, 2 ) * exp ( - ( T * length / Vat ) ) - betta;
	delta = delta / 2;
	delta = delta / numberOfGrowthCones;
	TRACE("neurite", "Solved dendrite equation of neuron with id %d and growth cone id %d", NeuronId, growthConeId);
	return delta;
};

bool Dendrite::solveEmbranchmentEquation(int growthConeId) {
	return false;
};