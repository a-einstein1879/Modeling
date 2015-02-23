#ifndef CELLSTACK_H
#define CELLSTACK_H

#include "cmn_struct.h"

class CellStack {
private:
	static CellStack *p_CellStack;
	int numberOfCells;
	//TODO: Use cells struct instead of this
	struct Cell *cells;
public:
	CellStack();
	~CellStack();
	static CellStack* getStack();
	int stackPush(struct Cell cell);
	struct Cell stackPull();
	bool isEmpty();
	bool isFull();
	void PrintStack();
};

#endif