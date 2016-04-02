#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "ui.h"
#include "hippocampus.h"
#include "environment.h"
#include "output.h"

class Processor {
private:
	UI *ui;
	Hippocampus *hippocampus;
	Environment *environment;
	Output *output;
	void tick(int t);
public:
	Processor();
	void Run();
};

#endif