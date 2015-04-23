#include "neurite.h"
#include "environment.h"
#include "cmn_defines.h"

Neurite::Neurite() {
	numberOfGrowthCones      = 0;
	numberOfTerminalElements = 0;
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
		growthCones[numberOfGrowthCones - 1].setNeuronType(neuronType);
	}
};

void Neurite::setCoordinates(Coordinates coord) {
	ENTER_FUNCTION("neurite", "setCoordinates(Coordinates coord)", "Neurite NeuronId = %d", NeuronId);
	coordinates = coord;
	//TODO:Growth cone coordinates shouldn`t be set here. Think where to move initialisation
	addGrowthCone();
	growthCones[0].setCoordinates(coordinates);
};

void Neurite::setNeuronId(int newId) {
	ENTER_FUNCTION("neurite", "setNeuronId(int newId)", "newId = %d", newId);
	NeuronId = newId;
};

void Neurite::setType(int Type) {
	ENTER_FUNCTION("neurite", "setType(int Type)", "Type = %d", Type);
	type = Type;
};

void Neurite::setNeuronType(int Type) {
	ENTER_FUNCTION("neurite", "setNeuronType(int Type)", "Type = %d", Type);
	neuronType = Type;
};

double Neurite::getGrowthConeDistance(int growthConeId) {
	return growthCones[growthConeId].getSomaDistance();
};

void Neurite::growNeurite(int growthConeId, double delta, int branching) {
	ENTER_FUNCTION("neurite", "growNeurite(int growthConeId, double delta, bool branching)", "growthConeId = %d, delta = %.2f, branching = %d", growthConeId, delta, branching);
	if(branching == 1 && numberOfGrowthCones >= MAXNUMBEROFGROWTHCONES) {branching = 0; TRACE("neurite", "Branching disabled. Max number of growth cones exceeded");}
	if(growthCones[growthConeId].isGrowthEnabled()) {
		Coordinates oldCoordinates = growthCones[growthConeId].getCoordinates();

		//get direction from environment
		struct Direction direction;
		Environment *environment = environment->getEnvironment();
		direction = environment->getDirection(oldCoordinates, neuronType);

		if (branching == 1) {
			struct Direction twoDirections[2];
			getTwoDirections(direction, twoDirections);
#ifdef BRANCHINGTRACES
			TRACE("neurite", "It`s time to branch now for neuron with neuron id %d and growth cone id %d", NeuronId, growthConeId);
#endif
			increaseGrowthConeCentrifugalOrder(growthConeId);
			addGrowthCone(growthConeId);

			growGrowthCone(oldCoordinates, delta, twoDirections[0], type, NeuronId, numberOfGrowthCones - 1);

			growGrowthCone(oldCoordinates, delta, twoDirections[1], type, NeuronId, growthConeId);
		}
		else {
			growGrowthCone(oldCoordinates, delta, direction, type, NeuronId, growthConeId);
			// Second check is added for case growth was disabled while growing out of bounds
			if (branching == -1 && growthCones[growthConeId].isGrowthEnabled()) {disableGrowth(growthConeId);}
		}
	}
};

void Neurite::growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId) {
	ENTER_FUNCTION("neurite", "growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId)",
		"delta = %.2f, direction.fi = %.2f, type = %d, NeuronId = %d, growthConeId = %d", delta, direction.fi, type, NeuronId, growthConeId);
	Coordinates newCoordinates = coord;
	double realDelta = newCoordinates.findNewCoordinates(coord, delta, direction, type, NeuronId, growthConeId);
	if (realDelta != -1) {
		growthCones[growthConeId].move(newCoordinates, realDelta);
	}
	else {
		TRACE("neurite", "realDelta == %.2f; disabling growth", realDelta);
		disableGrowth(growthConeId);
	}
};

void Neurite::disableGrowth(int growthConeId) {
	ENTER_FUNCTION("neurite", "disableGrowth(int growthConeId)", "growthConeId = %d", growthConeId);
	growthCones[growthConeId].disableGrowth();
	printTerminationStats(growthConeId);
	numberOfTerminalElements++;
	TRACE("neurite", "numberOfTerminalElements for neuron %d neurite is now %d", NeuronId, numberOfTerminalElements);
};

void Neurite::increaseGrowthConeCentrifugalOrder(int growthConeId) {
	ENTER_FUNCTION("neurite", "increaseGrowthConeCentrifugalOrder(int growthConeId)", "growthConeId = %d", growthConeId);
	printTerminationStats(growthConeId);
	growthCones[growthConeId].increaseCentrifugalOrder();
};

void Neurite::printTerminationStats(int growthConeId) {
	ENTER_FUNCTION("neurite", "printTerminationStats(int growthConeId)", "");
	int co = growthCones[growthConeId].getCentrifugalOrder();
	double length = growthCones[growthConeId].getSomaDistance() - growthCones[growthConeId].getPreviousLevelLength();
	TRACE("neurite", "Soma dist = %.2f. Previous length = %.2f", growthCones[growthConeId].getSomaDistance(), growthCones[growthConeId].getPreviousLevelLength());
	TRACE("neurite", "Level %d terminated. Length = %.2f", co, length);
#ifdef LENGTHSTATISTICS
	LENGTHSTATISTIC("%d\t%.2f", co, length);
#endif
};

#include <stdlib.h> /* For rand() */

void Neurite::tick() {
	ENTER_FUNCTION("neurite", "Neurite::tick()", "NeuronId = %d", NeuronId);
	double delta;
	int numberOfGrowthConesBeforeTick = numberOfGrowthCones;
	for(int i = 0; i < numberOfGrowthConesBeforeTick; i++) {
		growthCones[i].tick();
		if ( ( delta = solveEquation(i) ) > 0) {
			growNeurite(i, delta, solveEmbranchmentEquation(i));
		}
	}
};

#include <math.h>
double Axon::solveEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Axon::solveEquation(int growthConeId)", "growthConeId = %d", growthConeId);
	double delta;
	/* Coefficients below and formulas for growth are taken from Mironov, Semyanov, Kazantsev "Dendrite and axon specific geometrical adaptation in neurite development" */
	double alpha = 0.5;
	double betta = 1.1;
	double c0    = 14;
	double T     = 0.2927;
	double Vat   = 12;
	double k     = 0.035;
	double length = getGrowthConeDistance(growthConeId);
	delta = alpha * c0 * exp ( ( k - T / Vat ) * length ) - betta;
	TRACE("neurite", "Solved axon equation of neuron with id %d and growth cone id %d. Delta = %.2f", NeuronId, growthConeId, delta);
	return delta;
	//return 2;
};

int Axon::solveEmbranchmentEquation(int growthConeId) {
//	return rand()%2;
	return false;
};

#include <math.h>
double Dendrite::solveEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Dendrite::solveEquation(int growthConeId)", "growthConeId = %d", growthConeId);
	double delta;
	/* Coefficients below and formulas for growth are taken from Mironov, Semyanov, Kazantsev "Dendrite and axon specific geometrical adaptation in neurite development" */
	double alpha = 1.1;
	double betta = 1.18;
	double c0    = 14;
	double T     = 0.005;
	double Vat   = 40;
	double k     = 0.0001;
	double length = getGrowthConeDistance(growthConeId);
	delta = alpha * c0 * pow ( 1 + k * length, 2 ) * exp ( - ( T * length / Vat ) ) - betta;
	delta = delta / numberOfGrowthCones;
	TRACE("neurite", "Solved dendrite equation of neuron with id %d and growth cone id %d", NeuronId, growthConeId);
	return delta;
};

#include <math.h>
/* All statistic formulas are taken from Jaap van Pelt, Harry B.M. Uylings "Modeling Neuronal Growth and Shape" - pp 195-215 */
#define E     (double)1
#define D(t)  (double)1 //exp 
#define S     (double)1
#define gamma (double)growthCones[growthConeId].getCentrifugalOrder()
#define C(t)  (double)1
int Dendrite::solveEmbranchmentEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Dendrite::solveEmbranchmentEquation(int growthConeId)", "growthConeId = %d", growthConeId);
	/* Probability to create terminal segment */
	//if(rand()%10 / 10 > 0.8) {return -1;};
	double branchingProbability = D(t) * pow(numberOfGrowthCones, -E) * pow(2, - S * gamma) / C(t);
	if (branchingProbability > 1 || branchingProbability < 0) {TRACE("neurite", "ERROR!!!!!!!!!!!!!!!!!!branchingProbability < 0 or > 1\n\n\n\n\n\n\n");}
#ifdef BRANCHINGTRACES
	TRACE("neurite", "numberOfGrowthCones = %d, gamma = %.2f, branchingProbability = %.2f", numberOfGrowthCones, gamma, branchingProbability);
#endif
	double probability = double(rand()%100) / 100;
	TRACE("neurite", "chance = %.2f, %d", probability, probability < branchingProbability);
	if(probability < branchingProbability) {return 1;};
	return 0;
};
#undef E
#undef D
#undef S
#undef gamma
#undef C

Neurite& Neurite::operator=(Neurite &neurite) {
	type = neurite.getType();
	coordinates = neurite.getCoordinates();
	NeuronId    = neurite.getNeuronId();
	neuronType  = neurite.getNeuronType();

	numberOfGrowthCones = neurite.getNumberOfGrowthCones();
	for(int i = 0; i < numberOfGrowthCones; i++) {
		growthCones[i] = neurite.getGrowthCone(i);
	}
	return *this;
};

int Neurite::getType() {
	return type;
};

int Neurite::getNumberOfGrowthCones() {
	return numberOfGrowthCones;
};

GrowthCone Neurite::getGrowthCone(int growthConeId) {
	return growthCones[growthConeId];
};

Coordinates Neurite::getCoordinates() {
	return coordinates;
};

int Neurite::getNeuronId() {
	return NeuronId;
};

int Neurite::getNeuronType() {
	return neuronType;
};