#include "growthCone.h"
#include "cmn_defines.h"

GrowthCone& GrowthCone::operator=(GrowthCone &growthCone) {
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

double GrowthCone::getSomaDistance() {
	return somaDistance;
};

void GrowthCone::setCoordinates(Coordinates coord) {
	ENTER_FUNCTION("growthCone", "setCoordinates(Coordinates coord)", "");
	coordinates = coord;
	TRACE("growthCone", "Coordinates now are:");
	coordinates.PrintCoordinates();
};

Coordinates GrowthCone::getCoordinates() {
	return coordinates;
};

void GrowthCone::printStats() {
	ENTER_FUNCTION("growthCone", "printStats()", "");
#ifdef GROWTHCONETRACES
	TRACE("growthCone", "Growth cone stats. Soma distance = %.2f and coordinates are", getSomaDistance());
	coordinates.PrintCoordinates();
#endif
};