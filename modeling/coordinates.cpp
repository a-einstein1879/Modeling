#include "coordinates.h"
#include "cmn_defines.h"

Coordinates& Coordinates::operator=( Coordinates &coord ) {
	CoordX = coord.CoordX;
	CoordY = coord.CoordY;
	return *this;
};

void Coordinates::PrintCoordinates() {
	TRACE("coordinates", "X = %d\n", CoordX);
	TRACE("coordinates", "Y = %d\n", CoordY);
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

#include <math.h>
#include "cellStack.h"
#include "cmn_defines.h" //For NUMBEROFCELLSX and NUMBEROFCELLSY

void Coordinates::findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId) {
	for(int i = 1; i < delta; i++) {
		CoordX = oldCoordinates.GetX() + i * cos(direction.fi);
		CoordY = oldCoordinates.GetY() + i * sin(direction.fi);
		if(CoordX > NUMBEROFCELLSX - 1) {break;}
		if(CoordY > NUMBEROFCELLSY - 1) {break;}
		struct Cell cell;
		cell.coordinates.SetX(CoordX);
		cell.coordinates.SetY(CoordY);
		cell.cellType = cellType;
		cell.NeuronId = NeuronId;
        TRACE("Coordinates", "cell.cellType = %d, cell.NeuronId = %d\n", cell.cellType, cell.NeuronId);
		CellStack *cellStack = cellStack->getStack();
		if(!cellStack->isFull()) {cellStack->stackPush(cell);}
	}
};