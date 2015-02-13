#ifndef CELLSTACK_H
#define CELLSTACK_H

#include "cmn_struct.h"

class CellStack {
private:
	int numberOfCells;
	Coordinates *coordinates;
	int *cellType;
public:
	CellStack();
	~CellStack();
	int stackPush(struct Cell cell);
	struct Cell stackPull();
	bool isEmpty();
	bool isFull();
};

#endif