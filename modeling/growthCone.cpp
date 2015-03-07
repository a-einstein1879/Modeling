#include "growthCone.h"
#include "cmn_defines.h"

GrowthCone& GrowthCone::operator=( GrowthCone &growthCone ) {
	growthEnabled = growthCone.isGrowthEnabled();
	somaDistance = growthCone.getSomaDistance();
	coordinates = growthCone.getCoordinates();
	TRACE("growthCone", "Growth cone copied. Soma distance = %d and coordinates are\n", somaDistance);
	coordinates.PrintCoordinates();
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
	coordinates = coord;
	increaseSomaDistance(delta);
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
	TRACE("growthCone", "Growth cone stats. Soma distance = %d and coordinates are\n", somaDistance);
	coordinates.PrintCoordinates();
};