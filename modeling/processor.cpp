#include "processor.h"

//For pause
#include <cstdlib>


Processor::Processor() {
	hippocampus = new Hippocampus[1];
	gui = new GUI[1];
	gui->addHippocampus(hippocampus);
};

void Processor::Tick() {
	gui->tick();
	hippocampus->tick();
};

void Processor::Run() {
	int i = 0;
	while(i < 5) {
		i++;
		Tick();
	}
	system("pause");
};