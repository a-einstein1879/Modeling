#ifndef UI_H
#define UI_H

#include "hippocampus.h"
#ifdef GUI
#include <windows.h>
#endif

class UI {
private:
	static UI *p_UI;
	UI();
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
	Output *output;

	double environmentField[NUMBEROFCELLSX][NUMBEROFCELLSY][NUMBEROFNEURONTYPES];
	void printEnvironment();
public:
	static UI* getUI();
	~UI();

	void tick();
};

#endif