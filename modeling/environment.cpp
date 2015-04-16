#include "cmn_defines.h"
#include "environment.h"

Environment::Environment() {
	numberOfSources = 0;
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			for(int k = 0; k < NUMBEROFNEURONTYPES; k++)
				field[i][j][k] = 0;
};

Environment* Environment::p_environment = 0;

Environment* Environment::getEnvironment() {
	if(!p_environment)
		p_environment = new Environment();
	return p_environment;
};

double interaction(int type1, int type2) {
	if(type1 == 0 && type2 == 0) {return INTERACTION00;}
	if(type1 == 0 && type2 == 1) {return INTERACTION01;}
	if(type1 == 1 && type2 == 0) {return INTERACTION10;}
	if(type1 == 1 && type2 == 1) {return INTERACTION11;}
};

#if (NUMBEROFDIMENSIONS == 2)
#define DX(x, y, type) ( double( field[x + 1][y][type] - field[x][y][type] / 1.0 ) )
#define DY(x, y, type) ( double( field[x][y + 1][type] - field[x][y][type] / 1.0 ) )
// / pow( pow(DX(x, y, type), 2.0) + pow(DY(x, y, type), 2.0) , 0.5 ) )
#endif
#define _USE_MATH_DEFINES //for Pi in visual studio 2009 and earlier
#include <math.h> //For pi
struct Direction Environment::getDirection(Coordinates coord, int type) {
	ENTER_FUNCTION("environment", "getDirection(Coordinates coord, int type)", "type = %d, coordinates:", type);
	coord.PrintCoordinates();
	struct Direction direction;
#if (NUMBEROFDIMENSIONS == 2)
	int x = coord.GetX(), y = coord.GetY();
	double dx = 0, dy = 0;
	for(int i = 0; i < NUMBEROFNEURONTYPES; i++) {
		dx += interaction(i, type) * DX(x, y, i);
		dy += interaction(i, type) * DY(x, y, i);
	}
	if(dx != 0 && dy != 0) {
		double angleCos = dx / pow( pow(dx, 2.0) + pow(dy, 2.0) , 0.5 );
		direction.fi = acos(angleCos);
		TRACE("environment", "Angle counted. AngleCos = %.2f; angle = %.2f", angleCos, direction.fi);
	} else {
		direction.fi = double(rand()%16) / 16.0 * 2 * M_PI;
		TRACE("environment", "Random angle");
	}

#endif
	return direction;
};

#define numberOfIterations 20
#define h                  1
#define c                  1
#define tau                1
#define d                  0.01
#define k                  0.01
#define dxxField(x, y)     ( ( field[x + 1][y][type] - 2 * field[x][y][type] + field[x - 1][y][type] ) / double(h * h) )
#define dyyField(x, y)     ( ( field[x][y + 1][type] - 2 * field[x][y][type] + field[x][y - 1][type] ) / double(c * c) )
//#define sTotal(x, y)       ( (numberOfSources > 0 ) ? ( TriS(x, y, sources[0].GetX(), sources[0].GetY()) ) : 0 )
/*\
	double value = 0;                                \
	for(int i = 0; i < numberOfSources; i++)         \
		value += TriS(x, y, sources[i].GetX(), sources[i].GetY());*/
void Environment::solveEquation(int type) {
	double tmpField[NUMBEROFCELLSX][NUMBEROFCELLSY];
	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
				tmpField[i][j] = 0;

	int iteration = 0;
	while(iteration < numberOfIterations) {
		for(int i = 1; i < NUMBEROFCELLSX - 1; i++)
			for(int j = 1; j < NUMBEROFCELLSY - 1; j++)
				tmpField[i][j] = field[i][j][type] + tau * d * ( dxxField(i, j) + dyyField(i, j) ) - k * field[i][j][type];

		for(int i = 1; i < NUMBEROFCELLSX - 1; i++)
			for(int j = 1; j < NUMBEROFCELLSY - 1; j++)
					field[i][j][type] = tmpField[i][j];
		iteration++;
	}
};
#undef numberOfIterations
#undef h
#undef c
#undef tau
#undef d
#undef k
#undef dxxField
#undef dyyField
//#undef sTotal

void Environment::addSource(Coordinates coord, int type) {
	ENTER_FUNCTION("environment", "addSource(Coordinates coord)", "Coordinates are:", );
	coord.PrintCoordinates();
	dynamicArrayRealloc(Coordinates, sources, numberOfSources);
	sources[numberOfSources - 1] = coord;
	field[sources[numberOfSources - 1].GetX()][sources[numberOfSources - 1].GetY()][type] = 1;
};

// Every tick growth cones signalize themselves and they become sources for next tick.
void Environment::tick() {
	ENTER_FUNCTION("environment", "Environment::tick()", "",);
	for(int i = 0; i < NUMBEROFNEURONTYPES; i++)
		solveEquation(i);

#ifdef DIFFUSIONVISIBLE
	printf("Type 0:\n");
	for(int j = 0; j < NUMBEROFCELLSY; j++) {
		for(int i = 0; i < NUMBEROFCELLSX; i++)
			printf("%.3f ", field[i][j][0]);
		printf("\n");
	}
	printf("Type 1:\n");
	for(int j = 0; j < NUMBEROFCELLSY; j++) {
		for(int i = 0; i < NUMBEROFCELLSX; i++)
			printf("%.3f ", field[i][j][1]);
		printf("\n");
	}
	printf("\n");
#endif

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			for(int k = 0; k < NUMBEROFNEURONTYPES; k++)
				field[i][j][k] = 0;
	if(numberOfSources != 0) {
		delete [] sources;
	}
	numberOfSources = 0;
};