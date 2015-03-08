#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "cmn_struct.h"
#include "coordinates.h"

class Environment {
private:
	static Environment* p_environment;

	int numberOfSources;
	Coordinates *sources;

	void solveEquation();
public:
	static Environment* Environment::getEnvironment();

	struct Direction getDirection(Coordinates coord);
	void addSource(Coordinates coord);

	void tick();
};

#endif