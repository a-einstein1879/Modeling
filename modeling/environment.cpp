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