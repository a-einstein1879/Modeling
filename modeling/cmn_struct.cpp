#include "cmn_struct.h"

Cell& Cell::operator=( Cell &cell ) {
	coordinates  = cell.coordinates;
	cellType     = cell.cellType;
	NeuronId     = cell.NeuronId;
	NeuriteId    = cell.NeuriteId;
	growthConeId = cell.growthConeId;
	IsEmpty      = cell.isEmpty();
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