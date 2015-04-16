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
	void Tick();
public:
	Processor();
	void Run();
};

#endif