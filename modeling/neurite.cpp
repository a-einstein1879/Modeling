#include "neurite.h"
#include "environment.h"
#include "cmn_defines.h"

Neurite::Neurite() {
	numberOfGrowthCones = 0;
	addGrowthCone();
};

void Neurite::addGrowthCone(int growthConeId) {
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
			growGrowthCone(oldCoordinates, delta, direction, type, NeuronId, growthConeId);
		}
	}
};

void Neurite::growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId) {
		TRACE("neurite", "Growth cone %d with neuron id %d grows by %e\n", growthConeId, NeuronId, delta);
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
			growNeurite(i, delta, solveEmbranchmentEquation(i));
		}
};

#include <math.h>
double Axon::solveEquation(int growthConeId) {
	double delta;
	double length = getGrowthConeDistance(growthConeId);
	/* Formula below and coefficients are taken from Mironov, Semyanov, Kazantsev "Dendrite and axon specific geometrical adaptation in neurite development" */
	double alpha = 1.1;
	double betta = 1.18;
	double c0    = 14;
	double T     = 0.005;
	double Vat   = 40;
	double k     = 0.00005;
	delta = alpha * c0 * exp ( ( k - T / Vat ) * length ) - betta;
	TRACE("neurite", "Solving equation of neuron with id %d and growth cone id %d\n", NeuronId, growthConeId);
	return 3;
};

/* For rand() */
#include <stdlib.h>
bool Axon::solveEmbranchmentEquation(int growthConeId) {
	//return rand();
	return false;
};

double Dendrite::solveEquation(int growthConeId) {
	return 1;
};

bool Dendrite::solveEmbranchmentEquation(int growthConeId) {
	return true;
};