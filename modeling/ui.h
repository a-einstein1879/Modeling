#ifndef UI_H
#define UI_H

#include "hippocampus.h"
//#include <windows.h>

class GUI {
private:
//	HWND hwnd;
//	HDC hdc;

	int oldTwoDpicture[NUMBEROFCELLSX][NUMBEROFCELLSY];
	int TwoDpicture[NUMBEROFCELLSX][NUMBEROFCELLSY];
	Hippocampus* hippocampus;
	void create2Dpicture();
	void print2Dpicture();
	void getHippocampusCoordinates();
public:
	GUI();
	~GUI();
	void tick();
	void addHippocampus(Hippocampus* hippo);
};

#endif