#include "cmn_defines.h"
#include "environment.h"

Environment* Environment::p_environment = 0;

Environment* Environment::getEnvironment() {
	if(!p_environment)
		p_environment = new Environment();
	return p_environment;
};

struct Direction Environment::getDirection(Coordinates coord) {
	struct Direction direction;
	direction.fi = 0;
	return direction;
};

void Environment::solveEquation() {};

void Environment::addSource(Coordinates coord) {
	dynamicArrayRealloc(Coordinates, sources, numberOfSources);
};

void Environment::tick() {
	solveEquation();
	/*if(numberOfSources != 0) {
		delete [] sources;
	}*/
	int numberOfSources = 0;
	
	// Every tick growth cones signalize themselves and they become sources for next tick.
};