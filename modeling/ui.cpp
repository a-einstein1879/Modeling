#include "ui.h"
#include "cmn_defines.h"

void GUI::create2Dpicture() {
	getHippocampusCoordinates();
	if (NUMBEROFDIMENSIONS == 2) {return;}
};

#include <stdio.h>
void GUI::print2Dpicture() {
	for(int j = 0; j < NUMBEROFCELLSY; j++) {
		for(int i = 0; i < NUMBEROFCELLSX; i++)
			printf("%d ", TwoDpicture[i][j]);
		printf("\n");
	}
};

void GUI::getHippocampusCoordinates() {
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			TwoDpicture[i][j] = hippocampus->getFieldType(i, j);
};

/* Interface */
void GUI::tick() {
	TRACE("GUI", "GUI tick\n");
	create2Dpicture();
	print2Dpicture();
};

void GUI::addHippocampus(Hippocampus* hippo) {
	hippocampus = hippo;
};