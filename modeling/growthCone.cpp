#include "growthCone.h"
#include "cmn_defines.h"

GrowthCone& GrowthCone::operator=( GrowthCone &growthCone ) {
	growthEnabled = isGrowthEnabled();
	somaDistance = getSomaDistance();
	coordinates = growthCone.getCoordinates();
	return *this;
};

GrowthCone::GrowthCone() {
	growthEnabled = true;
};

bool GrowthCone::isGrowthEnabled() {
	return growthEnabled;
};

void GrowthCone::move(Coordinates coord, int delta) {
	coordinates = coord;
	increaseSomaDistance(delta);
};

void GrowthCone::increaseSomaDistance(int delta) {
	somaDistance += delta;
};

int GrowthCone::getSomaDistance() {
	return somaDistance;
};

void GrowthCone::setCoordinates(Coordinates coord) {
	coordinates = coord;
};

Coordinates GrowthCone::getCoordinates() {
	return coordinates;
};