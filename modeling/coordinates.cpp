#include "coordinates.h"
#include "cmn_defines.h"

Coordinates& Coordinates::operator=( Coordinates &coord ) {
	CoordX = coord.CoordX;
	CoordY = coord.CoordY;
	return *this;
};

void Coordinates::PrintCoordinates() {
	TRACE("coordinates", "X = %d; Y = %d\n", CoordX, CoordY);
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

#define _USE_MATH_DEFINES //for Pi in visual studio 2009 and earlier
#include <math.h> //For sin, cos and pi
#include "cellStack.h"

double Coordinates::findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId) {
	TRACE("coordinates", "Finding new coordinates for neuron %d growth cone id %d\n", NeuronId, growthConeId);
	double realDelta;
	for(int i = 1; i < delta; i++) {
		int tmpCoordX = (int) ( (double)oldCoordinates.GetX() + (double)i * cos(direction.fi) );
		int tmpCoordY = (int) ( (double)oldCoordinates.GetY() + (double)i * sin(direction.fi) );
	
		if ( (tmpCoordX == CoordX) && (tmpCoordY == CoordY) ) {continue;}
		if((tmpCoordX > NUMBEROFCELLSX - 1) || (tmpCoordX < 1) ||
		   (tmpCoordY > NUMBEROFCELLSY - 1) || (tmpCoordX < 1) ) {break; realDelta = -1;}

		CoordX = tmpCoordX;
		CoordY = tmpCoordY;
		Cell cell;
		cell.coordinates.SetX(CoordX);
		cell.coordinates.SetY(CoordY);
		cell.cellType = cellType;
		cell.NeuronId = NeuronId;
		cell.growthConeId = growthConeId;
		CellStack *cellStack = cellStack->getStack();
		if(!cellStack->isFull()) {cellStack->stackPush(cell);}
	}
	realDelta = ( (CoordX - oldCoordinates.GetX())^2 + (CoordY - oldCoordinates.GetY())^2 ) ^ (1/2);
	return realDelta;
};

void getTwoDirections(struct Direction direction, struct Direction *twoDirections) {
	twoDirections[0].fi = direction.fi + M_PI / 4;
	twoDirections[1].fi = direction.fi - M_PI / 4;
};