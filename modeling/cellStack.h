#ifndef CELLSTACK_H
#define CELLSTACK_H

#include "cmn_struct.h"

class CellStack {
private:
	static CellStack *p_CellStack;
	int numberOfCells;
	Cell *cells;
public:
	CellStack();
	~CellStack();
	static CellStack* getStack();
	int stackPush(Cell cell);
	Cell stackPull();
	bool isEmpty();
	bool isFull();
	void PrintStack();
};

#endif