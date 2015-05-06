#include "cmn_struct.h"

Cell& Cell::operator=( Cell &cell ) {
	IsEmpty      = cell.isEmpty();
	coordinates  = cell.coordinates;
	cellType     = cell.cellType;
	NeuronId     = cell.NeuronId;
	NeuriteId    = cell.NeuriteId;
	growthConeId = cell.growthConeId;
	somaDistance = cell.somaDistance;
	return *this;
};

void Cell::makeEmpty() {
	IsEmpty = true;
};

void Cell::makeFull() {
	IsEmpty = false;
};;

bool Cell::isEmpty() {
	return IsEmpty;
};

void Cell::PrintCoordinates() {
	coordinates.PrintCoordinates();
};