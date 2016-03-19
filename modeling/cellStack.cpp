#include "cellStack.h"
#include "cmn_struct.h"
#include "cmn_defines.h"

#define CELLSTACKMAXNUMBEROFCELLS ( NUMBEROFCELLSX * NUMBEROFCELLSY / 4 )

CellStack* CellStack::p_CellStack = 0;

CellStack::CellStack() {
	ENTER_FUNCTION("cellStack", "CellStack::CellStack()", "");
#ifdef CELLSTACKTRACES
	TRACE("cellStack", "Cell stack created"); 
#endif
	numberOfCells = 0;
	cells = new Cell[numberOfCells];
};

CellStack::~CellStack() {
	delete [] cells;
};

CellStack* CellStack::getStack() {
	if(!p_CellStack)
		p_CellStack = new CellStack();
	return p_CellStack;
};

int CellStack::stackPush(Cell cell) {
	ENTER_FUNCTION("cellStack", "stackPush()", "");
	if (numberOfCells < CELLSTACKMAXNUMBEROFCELLS) {
		Cell *tmpCells;

		tmpCells = new Cell[numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			tmpCells[i] = cells[i];
		}

		delete [] cells;

		cells = new Cell[++numberOfCells];

		for(int i = 0; i < numberOfCells - 1; i++) {
			cells[i] = tmpCells[i];
		}

		delete [] tmpCells;

		cells[numberOfCells - 1] = cell;
#ifdef CELLSTACKTRACES
		TRACE("cellStack", "New element successfully pushed. Stack now has %d elements", numberOfCells);
		cell.PrintCoordinates();
#endif
		return 0;
	}
#ifdef CELLSTACKTRACES
	TRACE("cellStack", "ERROR:Can`t push to stack max number of elements exceeded");
#endif
	return 1;
};

Cell CellStack::stackPop() {
	ENTER_FUNCTION("cellStack", "stackPull()", "");
	Cell cell;
	cell.makeEmpty();

	if (!isEmpty()) {
		cell = cells[numberOfCells - 1];

		Cell *tmpCells;

		tmpCells = new Cell[--numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			tmpCells[i] = cells[i];
		}

		delete [] cells;

		cells = new Cell[numberOfCells];

		for(int i = 0; i < numberOfCells; i++) {
			cells[i] = tmpCells[i];
		}

		delete [] tmpCells;

#ifdef CELLSTACKTRACES
		TRACE("cellStack", "element successfully pulled from stack. Stack now has %d elements", numberOfCells);
		cell.PrintCoordinates();
#endif
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
	ENTER_FUNCTION("cellStack", "PrintStack", "");
	for(int i = 0; i < numberOfCells; i++) {
#ifdef CELLSTACKTRACES
		//TRACE("cellStack", "");
		TRACE("cellStack", "Type of element %d is %d, neuronId is %d, growthConeId is %d and coordinates are:", i, cells[i].cellType, cells[i].NeuronId, cells[i].growthConeId);
		cells[i].coordinates.PrintCoordinates();
#endif
	}
};