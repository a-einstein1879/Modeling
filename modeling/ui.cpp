#include "ui.h"
#include "cmn_defines.h"
#include "environment.h"

#ifdef GUI
#include <windows.h>

COLORREF bgColor       = RGB(0,   0,   0);
COLORREF neuronColor   = RGB(0,   255, 0);
COLORREF axonColor     = RGB(0,   0,   255);
COLORREF dendriteColor = RGB(255, 0,   0);
#endif

UI::UI() {
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			oldTwoDpicture[i][j] = NOTHING;

#ifdef GUI
	LPCTSTR ClsName = L"BasicApp";
	LPCTSTR WndName = L"A Simple Window";

	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	MoveWindow(hWnd, 0, 0, NUMBEROFCELLSX, NUMBEROFCELLSY, false);

	for(int j = 0; j < NUMBEROFCELLSY; j++) {
		for(int i = 0; i < NUMBEROFCELLSX; i++) {
			SetPixel(hdc, i, j, bgColor);
		}
	}
/*	LPCTSTR ClsName1 = L"BasicApp1";
	LPCTSTR WndName1 = L"A Simple Window1";
	HDC hdc1;

	HINSTANCE hInstance;
	WNDCLASSEX WndClsEx;
//CallWindowProc(
	WndClsEx.cbSize        = sizeof(WNDCLASSEX);
	WndClsEx.style         = CS_NOCLOSE;
//	WndClsEx.lpfnWndProc   = WndProcedure;
	WndClsEx.cbClsExtra    = 0;
	WndClsEx.cbWndExtra    = 0;
	WndClsEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClsEx.lpszMenuName  = NULL;
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hInstance     = hInstance;
	WndClsEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	int a = RegisterClassEx(&WndClsEx);

	hWnd1 = GetDesktopWindow();
	hWnd1 = CreateWindow(ClsName1, WndName1, WS_BORDER, 0, 0, NUMBEROFCELLSX, NUMBEROFCELLSY, hWnd1, NULL, hInstance, NULL);
	ShowWindow(hWnd1, SW_SHOWNORMAL);
	UpdateWindow(hWnd1);
	hdc1 = GetDC(hWnd1);

	HPEN hPen;
	hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 25, 5));
	SelectObject(hdc1, hPen);
	Ellipse(hdc1, 90, 90, 120, 120);*/

#endif
};

UI::~UI() {
#ifdef GUI
	ReleaseDC(hWnd, hdc);
	DeleteDC(hdc);
#endif
};

void UI::create2Dpicture() {
	getHippocampusCoordinates();
	if (NUMBEROFDIMENSIONS == 2) {return;}
};

#include <stdio.h>
#include <cstdlib>
void UI::print2Dpicture() {
	if(changed == false) {return;}
#ifdef GUI
	for(int j = 0; j < NUMBEROFCELLSY; j++)
		for(int i = 0; i < NUMBEROFCELLSX; i++) {
			if (TwoDpicture[i][j] == oldTwoDpicture[i][j]) {continue;}
			if (TwoDpicture[i][j] == NEURON)  {SetPixel(hdc, i, j, neuronColor);};
			if (TwoDpicture[i][j] == AXON)    {SetPixel(hdc, i, j, axonColor);};
			if (TwoDpicture[i][j] == DENDRITE){SetPixel(hdc, i, j, dendriteColor);};
		}
#endif

#ifdef CLUI
#ifdef TRACEINFILE
#ifndef STEPBYSTEP
	if(system("CLS")) system("clear");
#endif
#endif
	for(int j = 0; j < NUMBEROFCELLSY; j++) {
		for(int i = 0; i < NUMBEROFCELLSX; i++)
			printf("%d ", TwoDpicture[i][j]);
		printf("\n");
	}
	printf("\n");
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			oldTwoDpicture[i][j] = TwoDpicture[i][j];
#endif
#ifdef STEPBYSTEP
	system("pause");
#endif
};

void UI::getHippocampusCoordinates() {
	changed = false;
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++) {
			TwoDpicture[i][j] = hippocampus->getFieldType(i, j);
			if (oldTwoDpicture[i][j] != TwoDpicture[i][j]) {changed = true;};
		}
};

void UI::printEnvironment() {
#if defined(DIFFUSIONVISIBLE) || defined(ENVIRONMENTSTATISTICS)
	Environment *environment;
	environment = environment->getEnvironment();
	for(int x = 0; x < NUMBEROFCELLSX; x++)
		for(int y = 0; y < NUMBEROFCELLSY; y++)
			for(int type = 0; type < NUMBEROFNEURONTYPES; type++)
				environmentField[x][y][type] = environment->getField(x, y, type);
#endif

#ifdef DIFFUSIONVISIBLE
	for(int type = 0; type < NUMBEROFNEURONTYPES; type++) {
		printf("Type %d:\n", type);
		for(int y = 0; y < NUMBEROFCELLSY; y++) {
			for(int x = 0; x < NUMBEROFCELLSX; x++)
				printf("%.3f ", environmentField[x][y][type]);
			printf("\n");
		}
		printf("\n");
	}
#endif

#ifdef ENVIRONMENTSTATISTICS
	FILE *file;
	fopen_s(&file, ENVIRONMENTSTATISTICSFILE, "a");
	fprintf(file, "\n");
	for(int type = 0; type < NUMBEROFNEURONTYPES; type++) {
	//	fprintf(file, "Type %d:\n", type);
		fprintf(file, "\n", type);
		for(int y = 0; y < NUMBEROFCELLSY; y++) {
			for(int x = 0; x < NUMBEROFCELLSX; x++)
				fprintf(file, "%.3f ", environmentField[x][y][type]);
			fprintf(file, "\n");
		}
		fprintf(file, "\n");
	}
	fclose(file);
#endif
};

/* Interface */
void UI::tick() {
	ENTER_FUNCTION("GUI", "GUI::tick()", "");
	printEnvironment();
	create2Dpicture();
	print2Dpicture();
};

void UI::addHippocampus(Hippocampus* hippo) {
	hippocampus = hippo;
};