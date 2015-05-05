#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "ui.h"
#include "hippocampus.h"
#include "environment.h"

class Processor {
private:
	UI *ui;
	Hippocampus *hippocampus;
	Environment *environment;
	void Tick(int t);
public:
	Processor();
	void Run();
};

#endif