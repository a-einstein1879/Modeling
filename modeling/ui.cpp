//#include "stdafx.h"
//#include "afxwin.h"
#include "ui.h"
#include "cmn_defines.h"

//#include <windows.h>

COLORREF color = RGB(0, 255, 0);
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

GUI::GUI() {
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			oldTwoDpicture[i][j] = NOTHING;

	/*LPCTSTR ClsName = L"BasicApp";
	LPCTSTR WndName = L"A Simple Window";
	HINSTANCE hInstance;

	WNDCLASSEX WndClsEx;*/

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
	/*RegisterClassEx(&WndClsEx);

	hWnd = CreateWindowEx(0, ClsName, WndName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	hWnd1 = GetTopWindow(hWnd);*/
		//CreateWindow(ClsName, WndName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWnd, NULL, hInstance, NULL);
	//GetConsoleWindow();
  /*LPCTSTR lpClassName,  // ��� ������
  LPCTSTR lpWindowName, // ��� ���� (������������  � ���������)
  DWORD dwStyle, // ����� ����
  int x,         // ����������  �� �����������  �� ������ ���� ������
  int y,         // ����������  �� ���������  �� �������� ���� ������
  int nWidth,    // ������ ����
  int nHeight,   // ������ ����
  HWND hWndParent, // ������������ ����
  HMENU hMenu,     // ��������� ����
  HINSTANCE hInstance, // ��������� ����������
  LPVOID lpParam       // ��������; ������ ������� NULL
);*/
	/*ShowWindow(hWnd1, SW_SHOWNORMAL);
	UpdateWindow(hWnd1);
	hdc = GetDC(hWnd1);
	for(int j = 0; j < NUMBEROFCELLSY; j++)
		for(int i = 0; i < NUMBEROFCELLSX; i++) {
			;
			SetPixel(hdc, i, j, color);
		}*/
};

GUI::~GUI() {
	/*ReleaseDC(hWnd, hdc);
	DeleteDC(hdc);*/
};

void GUI::create2Dpicture() {
	getHippocampusCoordinates();
	if (NUMBEROFDIMENSIONS == 2) {return;}
};

#include <stdio.h>
void GUI::print2Dpicture() {
/*	for(int j = 0; j < NUMBEROFCELLSY; j++)
		for(int i = 0; i < NUMBEROFCELLSX; i++) {
			if (TwoDpicture[i][j] == oldTwoDpicture[i][j]) {continue;}
			if (TwoDpicture[i][j] == NEURON) {};
			if (TwoDpicture[i][j] == AXON)   {};
		}*/
	
	for(int j = 0; j < NUMBEROFCELLSY; j++) {
		for(int i = 0; i < NUMBEROFCELLSX; i++)
			printf("%d ", TwoDpicture[i][j]);
		printf("\n");
	}
	printf("\n");
};

void GUI::getHippocampusCoordinates() {
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			TwoDpicture[i][j] = hippocampus->getFieldType(i, j);
};

/* Interface */
void GUI::tick() {
	ENTER_FUNCTION("GUI", "GUI::tick()", "");
	create2Dpicture();
	print2Dpicture();
};

void GUI::addHippocampus(Hippocampus* hippo) {
	hippocampus = hippo;
};