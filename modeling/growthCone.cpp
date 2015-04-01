#include "growthCone.h"
#include "cmn_defines.h"

GrowthCone& GrowthCone::operator=( GrowthCone &growthCone ) {
	growthEnabled = growthCone.isGrowthEnabled();
	somaDistance  = growthCone.getSomaDistance();
	coordinates   = growthCone.getCoordinates();
	return *this;
};

GrowthCone::GrowthCone() {
	growthEnabled = true;
	somaDistance  = 0;
};

void GrowthCone::disableGrowth() {
	growthEnabled = false;
};

bool GrowthCone::isGrowthEnabled() {
	return growthEnabled;
};

void GrowthCone::move(Coordinates coord, double delta) {
	ENTER_FUNCTION("growthCone", "move(Coordinates coord, double delta)", "delta = %d", delta);
	coordinates = coord;
	increaseSomaDistance(delta);
	printStats();
};

void GrowthCone::increaseSomaDistance(double delta) {
	somaDistance += delta;
};

double GrowthCone::getSomaDistance() {
	return somaDistance;
};

void GrowthCone::setCoordinates(Coordinates coord) {
	coordinates = coord;
};

Coordinates GrowthCone::getCoordinates() {
	return coordinates;
};

void GrowthCone::printStats() {
	ENTER_FUNCTION("growthCone", "printStats()", "");
#ifdef GROWTHCONETRACES
	TRACE("growthCone", "Growth cone stats. Soma distance = %.1e and coordinates are", getSomaDistance());
	coordinates.PrintCoordinates();
#endif
};