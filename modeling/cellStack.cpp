#include "cellStack.h"
#include "cmn_struct.h"
#include "cmn_defines.h"

#define CELLSTACKMAXNUMBEROFCELLS ( NUMBEROFCELLSX * NUMBEROFCELLSY / 4 )

CellStack* CellStack::p_CellStack = 0;

CellStack::CellStack() {
	TRACE("CellStack", "Cell stack created\n"); 
	numberOfCells = 0;
	cells = new struct Cell[numberOfCells];
};

CellStack::~CellStack() {
	delete [] cells;
};

CellStack* CellStack::getStack() {
	if(!p_CellStack)
		p_CellStack = new CellStack();
	return p_CellStack;
};

int CellStack::stackPush(struct Cell cell) {
	if (numberOfCells < CELLSTACKMAXNUMBEROFCELLS) {
		struct Cell *tmpCells;

		tmpCells = new struct Cell[numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			tmpCells[i].coordinates = cells[i].coordinates;
			tmpCells[i].cellType    = cells[i].cellType;
			tmpCells[i].NeuronId    = cells[i].NeuronId;
		}

		delete [] cells;

		cells = new struct Cell[++numberOfCells];

		for(int i = 0; i < numberOfCells - 1; i++) {
			cells[i].coordinates = tmpCells[i].coordinates;
			cells[i].cellType    = tmpCells[i].cellType;
			cells[i].NeuronId    = tmpCells[i].NeuronId;
		}

		delete [] tmpCells;

		cells[numberOfCells - 1].coordinates = cell.coordinates;
		cells[numberOfCells - 1].cellType    = cell.cellType;
		cells[numberOfCells - 1].NeuronId    = cell.NeuronId;
		TRACE("CellStack", "New element successfully pushed. Stack now has %d elements\n", numberOfCells);
		PrintStack();
		return 0;
	}
	TRACE("CellStack", "ERROR:Can`t push to stack max number of elements exceeded\n");
	return 1;
};

struct Cell CellStack::stackPull() {
	struct Cell cell;

	if (!isEmpty()) {
		cell.coordinates = cells[numberOfCells - 1].coordinates;
		cell.cellType    = cells[numberOfCells - 1].cellType;
		cell.NeuronId    = cells[numberOfCells - 1].NeuronId;

		struct Cell *tmpCells;

		tmpCells = new struct Cell[--numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			tmpCells[i].coordinates = cells[i].coordinates;
			tmpCells[i].cellType    = cells[i].cellType;
			tmpCells[i].NeuronId    = cells[i].NeuronId;
		}

		delete [] cells;

		cells = new struct Cell[numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			cells[i].coordinates = tmpCells[i].coordinates;
			cells[i].cellType    = tmpCells[i].cellType;
			cells[i].NeuronId    = tmpCells[i].NeuronId;
		}


		TRACE("CellStack", "Element successfully pulled from stack. Stack now has %d elements\n", numberOfCells);
		PrintStack();
		return cell;
	}
	return cell;
};

bool CellStack::isEmpty() {
	return (numberOfCells == 0)?1:0;
};
bool CellStack::isFull() {
	return (numberOfCells == CELLSTACKMAXNUMBEROFCELLS)?1:0;
};

void CellStack::PrintStack() {
	for(int i = 0; i < numberOfCells; i++) {
		TRACE("CellStack", "Type of new element %d is %d, neuronId is %d and coordinates are:\n", i, cells[i].cellType, cells[i].NeuronId);
		cells[i].coordinates.PrintCoordinates();
	}
};