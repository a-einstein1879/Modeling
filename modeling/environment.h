#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "cmn_struct.h"

class Environment {
private:
	static Environment* p_environment;
public:
	static Environment* Environment::getEnvironment();
	struct Direction getDirection(Coordinates coord);
};

#endif