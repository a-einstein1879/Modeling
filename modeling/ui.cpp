//#include "stdafx.h"
//#include "afxwin.h"
#include "ui.h"
#include "cmn_defines.h"

#ifdef GUI
#include <windows.h>

COLORREF bgColor       = RGB(0,   0,   0);
COLORREF neuronColor   = RGB(0,   255, 0);
COLORREF axonColor     = RGB(255, 0,   0);
COLORREF dendriteColor = RGB(0,   0,   255);
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

UI::UI() {
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			oldTwoDpicture[i][j] = NOTHING;

#ifdef GUI
	LPCTSTR ClsName = L"BasicApp";
	LPCTSTR WndName = L"A Simple Window";
	HINSTANCE hInstance;

	WNDCLASSEX WndClsEx;

	// Create the application window
	/*WndClsEx.cbSize        = sizeof(WNDCLASSEX);
	WndClsEx.style         = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc   = WndProcedure;
	WndClsEx.cbClsExtra    = 0;
	WndClsEx.cbWndExtra    = 0;
	WndClsEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClsEx.lpszMenuName  = NULL;
	WndClsEx.lpszClassName = ClsName;
	WndClsEx.hInstance     = hInstance;
	WndClsEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);*/

	// Register the application
	RegisterClassEx(&WndClsEx);

	hWnd = CreateWindowEx(0, ClsName, WndName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	hWnd1 = CreateWindow(ClsName, WndName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWnd, NULL, hInstance, NULL);
		//GetTopWindow(hWnd);
	//GetConsoleWindow();
  /*LPCTSTR lpClassName,  // им€ класса
  LPCTSTR lpWindowName, // им€ окна (отображаетс€  в заголовке)
  DWORD dwStyle, // стиль окна
  int x,         // координата  по горизонтали  от левого кра€ экрана
  int y,         // координата  по вертикали  от верхнего кра€ экрана
  int nWidth,    // ширина окна
  int nHeight,   // высота окна
  HWND hWndParent, // родительское окно
  HMENU hMenu,     // описатель меню
  HINSTANCE hInstance, // экземпл€р приложени€
  LPVOID lpParam       // параметр; всегда ставьте NULL
);*/
	ShowWindow(hWnd1, SW_SHOWNORMAL);
	UpdateWindow(hWnd1);
	hdc = GetDC(hWnd1);
	for(int j = 0; j < NUMBEROFCELLSY; j++)
		for(int i = 0; i < NUMBEROFCELLSX; i++) {
			;
			SetPixel(hdc, i, j, bgColor);
		}
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
	if (system("CLS")) system("clear");
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
};

void UI::getHippocampusCoordinates() {
	changed = false;
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++) {
			TwoDpicture[i][j] = hippocampus->getFieldType(i, j);
			if (oldTwoDpicture[i][j] != TwoDpicture[i][j]) {changed = true;};
		}
};

/* Interface */
void UI::tick() {
	ENTER_FUNCTION("GUI", "GUI::tick()", "");
	create2Dpicture();
	print2Dpicture();
};

void UI::addHippocampus(Hippocampus* hippo) {
	hippocampus = hippo;
};