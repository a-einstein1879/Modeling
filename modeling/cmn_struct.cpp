#include "cmn_struct.h"

Cell& Cell::operator=( Cell &cell ) {
	coordinates  = cell.coordinates;
	cellType     = cell.cellType;
	NeuronId     = cell.NeuronId;
	NeuriteId    = cell.NeuriteId;
	growthConeId = cell.growthConeId;
	return *this;
};

void Cell::makeEmpty() {
	IsEmpty = true;
};

bool Cell::isEmpty() {
	return IsEmpty;
};