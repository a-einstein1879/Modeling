#include "processor.h"
#include "cmn_defines.h"
#include "environment.h"

//For pause
#include <cstdlib>


Processor::Processor() {
	hippocampus = new Hippocampus[1];
	gui = new GUI[1];
	gui->addHippocampus(hippocampus);
	environment = environment->getEnvironment();
};

void Processor::Tick() {
	environment->tick();
	hippocampus->tick();
	gui->tick();
};

#include <ctime>    /* For time(0) seed */
void Processor::Run() {
	srand(time(0));
	int i = 0;
	while(i < WORKTIME) {
		i++;
		Tick();
	}
	system("pause");
};