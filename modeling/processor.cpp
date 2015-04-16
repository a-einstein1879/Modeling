#include "processor.h"
#include "cmn_defines.h"
#include "environment.h"

//For pause
#include <cstdlib>


Processor::Processor() {
	hippocampus = new Hippocampus[1];
	ui = new UI[1];
	ui->addHippocampus(hippocampus);
	environment = environment->getEnvironment();
};

/*
Environment tick is the first tick. While this tick equations are solved and all growth cones will get directions after solving equation.
After tick all sources are deleted from environment to be refreshed on next hippocampus tick
Then happens hippocampus tick where equations for all neurons are solved. All neurons while ticking signalize themselves to environment
*/
void Processor::Tick() {
	environment->tick();
	hippocampus->tick();
	ui->tick();
};

#include <ctime>    /* For time(0) seed */
void Processor::Run() {
	ENTER_FUNCTION("processor", "Processor::Run()", "");
	srand(time(0));
	int i = 0;
	while(i < WORKTIME) {
		i++;
		TRACE("processor", "tick(%d)", i);
		Tick();
	}
	system("pause");
};