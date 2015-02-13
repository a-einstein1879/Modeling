#include "cellStack.h"
#include "cmn_struct.h"
#include "cmn_defines.h"

#define CELLSTACKMAXNUMBEROFCELLS ( NUMBEROFCELLSX * NUMBEROFCELLSY / 4 )

CellStack::CellStack() {
	TRACE("CellStack", "Cell stack created\n"); 
	numberOfCells = 0;
};

CellStack::~CellStack() {
	delete [] coordinates;
	delete [] cellType;
};

int CellStack::stackPush(struct Cell cell) {
	if (numberOfCells < CELLSTACKMAXNUMBEROFCELLS) {
		Coordinates *tmpCoordinates;
		int *tmpCellType;

		tmpCoordinates = new Coordinates[numberOfCells];
		tmpCellType    = new int[numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			tmpCoordinates[i] = coordinates[i];
			tmpCellType[i]    = cellType[i];
		}

		coordinates = new Coordinates[++numberOfCells];
		cellType    = new int[numberOfCells];

		for(int i = 0; i < numberOfCells - 1; i++) {
			coordinates[i] = tmpCoordinates[i];
			cellType[i]    = tmpCellType[i];
		}

		delete [] tmpCoordinates;
		delete [] tmpCellType;

		coordinates[numberOfCells - 1] = cell.coordinates;
		cellType[numberOfCells - 1]    = cell.cellType;
		TRACE("CellStack", "New element successfully pushed. Stack now has %d elements\n", numberOfCells);
		return 0;
	}
	TRACE("CellStack", "ERROR:Can`t push to stack max number of elements exceeded\n");
	return 1;
};

struct Cell CellStack::stackPull() {
	if (!isEmpty()) {
		struct Cell cell;
		cell.coordinates = coordinates[numberOfCells - 1];
		TRACE("CellStack", "Element number %d pulled from stack\n", numberOfCells - 1);
		return cell;
	}
};

bool CellStack::isEmpty() {
	return (numberOfCells == 0)?1:0;
};
bool CellStack::isFull() {
	return (numberOfCells == CELLSTACKMAXNUMBEROFCELLS)?1:0;
};