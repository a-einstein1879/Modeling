#include "processor.h"

#include "cmn_struct.h"
#include "cellStack.h"
#include <stdio.h>

int main() {
/*	CellStack *cellStack = cellStack->getStack();
	Cell cell;

	for(int i = 0; i < 12000; i++) {
		cell.makeEmpty();
		cellStack->stackPush(cell);
	}

	system("pause");

	for(int i = 0; i < 15000; i++) {
		cell = cellStack->stackPull();
	}

	system("pause");
	*/

	
	Processor processor;
	processor.Run();
	return 0;
}