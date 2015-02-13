#ifndef UI_H
#define UI_H

#include "hippocampus.h"

class GUI {
private:
	int TwoDpicture[NUMBEROFCELLSX][NUMBEROFCELLSY];
	Hippocampus* hippocampus;
	void create2Dpicture();
	void print2Dpicture();
	void getHippocampusCoordinates();
public:
	void tick();
	void addHippocampus(Hippocampus* hippo);
};

#endif