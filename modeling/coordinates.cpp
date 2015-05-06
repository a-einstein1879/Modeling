#include "coordinates.h"
#include "cmn_defines.h"

Coordinates& Coordinates::operator=( Coordinates &coord ) {
	CoordX = coord.CoordX;
	CoordY = coord.CoordY;
	return *this;
};

void Coordinates::PrintCoordinates() {
	ENTER_FUNCTION("coordinates", "PrintCoordinates()", "");
	TRACE("coordinates", "X = %d; Y = %d", CoordX, CoordY);
	if(!XYCORRECTIONCHECKER(CoordX, CoordY)) {TRACE("coordinates", "ERROR!!!!!!!!!!!!!!!!!!\n\n\n\n\n\n\n");}
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

double Coordinates::findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId, int somaDistance) {
	ENTER_FUNCTION("coordinates", "findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId)",
		"delta = %.2f, direction.fi = %.2f, cellType = %d, NeuronId = %d, growthConeId = %d. Old coordinates:", delta, direction.fi, cellType, NeuronId, growthConeId);
	oldCoordinates.PrintCoordinates();
	double realDelta;
	double oldX = oldCoordinates.GetX();
	double oldY = oldCoordinates.GetY();
	if (delta < 1) {
		realDelta = 0;
	}
	else {
		CellStack *cellStack = cellStack->getStack();
		int tmpCoordX = (int) (double)oldX;
		int tmpCoordY = (int) (double)oldY;
		for(int i = 1; i <= delta; i++) {
			tmpCoordX = (int) ( (double)oldX + (double)i * cos(direction.fi) );
			tmpCoordY = (int) ( (double)oldY + (double)i * sin(direction.fi) );
		
			if ( (tmpCoordX == CoordX) && (tmpCoordY == CoordY) ) {continue;}
			if (!XYCORRECTIONCHECKER(tmpCoordX, tmpCoordY)) {return -1;}

			CoordX = tmpCoordX;
			CoordY = tmpCoordY;
			Cell cell;
			cell.makeFull();
			cell.coordinates.SetX(CoordX);
			cell.coordinates.SetY(CoordY);
			cell.cellType = cellType;
			cell.NeuronId = NeuronId;
			cell.growthConeId = growthConeId;
			cell.somaDistance = somaDistance + (int)findDistanceBetween((double)CoordX, (double)CoordY, oldX, oldY);
			if(!cellStack->isFull()) {cellStack->stackPush(cell);}
		}
		cellStack->PrintStack();
		if (CoordX == oldX && CoordY == oldY) {
			realDelta = 0;
		}
		else {
			realDelta = pow( pow( double(CoordX - oldX), 2 ) + pow( double(CoordY - oldY), 2 ), 0.5 );
		}
	}
	TRACE("coordinates", "After finding coordinates real delta is %.2f, new coordinates:", realDelta);
	PrintCoordinates();
	return realDelta;
};

double Coordinates::findDistanceBetween(double x1, double y1, double x2, double y2) {
	return (x1 == x2 && y1 == y2) ? 0 : pow( 
		                                pow( double(x1 - x2), 2 ) + 
		                                pow( double(y1 - y2), 2 )
										    , 0.5 );
};

void getTwoDirections(struct Direction direction, struct Direction *twoDirections) {
	twoDirections[0].fi = direction.fi + M_PI / 4;
	twoDirections[1].fi = direction.fi - M_PI / 4;
};