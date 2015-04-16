#include "growthCone.h"
#include "cmn_defines.h"

GrowthCone::GrowthCone() {
	growthEnabled       = true;
	somaDistance        = 0;
	centrifugalOrder    = 1;
	previousLevelLength = 0;
};

void GrowthCone::setCoordinates(Coordinates coord) {
	ENTER_FUNCTION("growthCone", "setCoordinates(Coordinates coord)", "");
	coordinates = coord;
	TRACE("growthCone", "Coordinates now are:");
	coordinates.PrintCoordinates();
};

void GrowthCone::setNeuronType(int Type) {
	ENTER_FUNCTION("growthCone", "setNeuronType(int Type)", "Type = %d", Type);
	neuronType = Type;
};

void GrowthCone::tick() {
	ENTER_FUNCTION("growthCone", "GrowthCone::tick()", "Coordinates are:");
	coordinates.PrintCoordinates();
	Environment *environment;
	environment = environment->getEnvironment();
	environment->addSource(coordinates, neuronType);
};

void GrowthCone::disableGrowth() {
	ENTER_FUNCTION("growthCone", "disableGrowth()", "Coordinates are:");
	coordinates.PrintCoordinates();
	growthEnabled = false;
};

bool GrowthCone::isGrowthEnabled() {
	return growthEnabled;
};

void GrowthCone::move(Coordinates coord, double delta) {
	ENTER_FUNCTION("growthCone", "move(Coordinates coord, double delta)", "delta = %.2f", delta);
	setCoordinates(coord);
	increaseSomaDistance(delta);
	printStats();
};

void GrowthCone::increaseSomaDistance(double delta) {
	ENTER_FUNCTION("growthCone", "increaseSomaDistance(double delta)", "delta = %.2f", delta);
	somaDistance += delta;
	TRACE("growthCone", "Soma distance is %.2f now", somaDistance);
};

void GrowthCone::increaseCentrifugalOrder() {
	ENTER_FUNCTION("growthCone", "increaseCentrifugalOrder()", "");
	centrifugalOrder++;
	previousLevelLength = somaDistance;
#ifdef BRANCHINGTRACES
	TRACE("growthCone", "Centrifugal order is now %d. previousLevelLength is %.2f", centrifugalOrder, previousLevelLength);
#endif
};

/*****************
	Interface
*****************/
GrowthCone& GrowthCone::operator=(GrowthCone &growthCone) {
	growthEnabled       = growthCone.isGrowthEnabled();
	somaDistance        = growthCone.getSomaDistance();
	coordinates         = growthCone.getCoordinates();
	centrifugalOrder    = growthCone.getCentrifugalOrder();
	previousLevelLength = growthCone.getPreviousLevelLength();
	neuronType          = growthCone.getNeuronType();
	return *this;
};

double GrowthCone::getSomaDistance() {
	return somaDistance;
};

double GrowthCone::getPreviousLevelLength(){
	return previousLevelLength;
};

Coordinates GrowthCone::getCoordinates() {
	return coordinates;
};

int GrowthCone::getCentrifugalOrder() {
	return centrifugalOrder;
};

int GrowthCone::getNeuronType() {
	return neuronType;
};

void GrowthCone::printStats() {
	ENTER_FUNCTION("growthCone", "printStats()", "");
#ifdef GROWTHCONETRACES
	TRACE("growthCone", "Growth cone stats. Soma distance = %.2f, centrifugalOrder = %d and coordinates are", getSomaDistance(), centrifugalOrder);
	coordinates.PrintCoordinates();
#endif
};