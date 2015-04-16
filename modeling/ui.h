#ifndef UI_H
#define UI_H

#include "hippocampus.h"
#ifdef GUI
#include <windows.h>
#endif

class UI {
private:
#ifdef GUI
	HWND hWnd, hWnd1;
	HDC hdc;
#endif

	int oldTwoDpicture[NUMBEROFCELLSX][NUMBEROFCELLSY];
	int TwoDpicture[NUMBEROFCELLSX][NUMBEROFCELLSY];
	bool changed;

	Hippocampus* hippocampus;
	void create2Dpicture();
	void print2Dpicture();
	void getHippocampusCoordinates();
public:
	UI();
	~UI();
	void tick();
	void addHippocampus(Hippocampus* hippo);
};

#endif