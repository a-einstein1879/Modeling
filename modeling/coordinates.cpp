#include "coordinates.h"
#include "cmn_defines.h"

Coordinates& Coordinates::operator=( Coordinates &coord ) {
	CoordX = coord.CoordX;
	CoordY = coord.CoordY;
	return *this;
};

void Coordinates::PrintCoordinates() {
	TRACE("Coordinates", "X = %d\nY = %d\n", CoordX, CoordY);
};

void Coordinates::SetX(int x) {
	CoordX = x;
};

void Coordinates::SetY(int y) {
	CoordY = y;
};

int Coordinates::GetX() {
	return CoordX;
};

int Coordinates::GetY() {
	return CoordY;
};