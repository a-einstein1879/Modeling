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
	ENTER_FUNCTION("environment", "Environment::getEnvironment()", "");
	if(!p_environment)
		p_environment = new Environment();
	return p_environment;
};

double interaction(int type1, int type2) {
	if(type1 == 0 && type2 == 0) {return INTERACTION00;}
	if(type1 == 0 && type2 == 1) {return INTERACTION01;}
	if(type1 == 1 && type2 == 0) {return INTERACTION10;}
	if(type1 == 1 && type2 == 1) {return INTERACTION11;}
	return 12;
};

#if (NUMBEROFDIMENSIONS == 2)
#define DX(x, y, type) ( double( field[x + 1][y][type] - field[x][y][type] / 1.0 ) )
#define DY(x, y, type) ( double( field[x][y + 1][type] - field[x][y][type] / 1.0 ) )
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
		if( (x > 0) && (y > 0) && x < NUMBEROFCELLSX - 1 && y < NUMBEROFCELLSY - 1 ) {
			dx += interaction(i, type) * DX(x, y, i);
			dy += interaction(i, type) * DY(x, y, i);
			TRACE("environment", "Gradient counted.\n\
field[x + 1][y][type] = %.3f, field[x][y][type] = %.3f\n\
field[x][y + 1][type] = %.3f, field[x][y][type] = %.3f\n\
x = %d, y = %d, Source = %d, destination = %d, dx = %.5f; dy = %.5f", 
field[x + 1][y][i], field[x][y][i], 
field[x][y + 1][i], field[x][y][i], x, y, i, type, dx, dy);
		}
	}
	if(dx != 0 && dy != 0) {
		double dr = pow( pow(dx, 2.0) + pow(dy, 2.0) , 0.5 );
		double angleCos = dx / dr;
		direction.fi = acos(angleCos);
		// Added some randomity to all directions
		direction.fi += double( rand()%8 - 4 ) * ( M_PI / 4 );
		if(dy < 0) {direction.fi = 2 * M_PI - direction.fi;}
		TRACE("environment", "Angle counted. dx = %.3f, dy = %.3f, dr = %.3f. AngleCos = %.2f; angle = %.2f", dx, dy, dr, angleCos, direction.fi);
	} else {
		direction.fi = double(rand()%16) / 16.0 * 2 * M_PI;
		TRACE("environment", "Random angle");
	}
	/*if(coord.GetX() < NUMBEROFCELLSX / 2) {direction.fi = 0;}
	else {direction.fi = M_PI/2;}*/

#endif
	return direction;
};
#undef DX
#undef DY

#define numberOfIterations 150
#define h                  1
#define c                  1
#define tau                1
#define d                  0.1
#define k                  0.001
#define dxxField(x, y)     ( ( field[x + 1][y][type] - 2 * field[x][y][type] + field[x - 1][y][type] ) / double(h * h) )
#define dyyField(x, y)     ( ( field[x][y + 1][type] - 2 * field[x][y][type] + field[x][y - 1][type] ) / double(c * c) )
//#define sTotal(x, y)       ( (numberOfSources > 0 ) ? ( TriS(x, y, sources[0].GetX(), sources[0].GetY()) ) : 0 )
/*\
	double value = 0;                                \
	for(int i = 0; i < numberOfSources; i++)         \
		value += TriS(x, y, sources[i].GetX(), sources[i].GetY());*/
void Environment::solveEquation(int type) {
	ENTER_FUNCTION("environment", "Environment::solveEquation(int type)", "type = %d", type);
	printSources();
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
	int x = sources[numberOfSources - 1].GetX(), y = sources[numberOfSources - 1].GetY();
	field[x][y][type] = 1;
	TRACE("environment", "Added source at (%d, %d)", x, y);
};

void Environment::printSources() {
	ENTER_FUNCTION("environment", "printSources()", "");
	//TODO: Add types to sources
	for(int i = 0; i < numberOfSources; i++)
		sources[numberOfSources - 1].PrintCoordinates();
};

double Environment::getField(int x, int y, int type) {
	return field[x][y][type];
};

// Every tick growth cones signalize themselves and they become sources for next tick.
void Environment::tick() {
	ENTER_FUNCTION("environment", "Environment::tick()", "");
	for(int i = 0; i < NUMBEROFNEURONTYPES; i++)
		solveEquation(i);

/*	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			for(int k = 0; k < NUMBEROFNEURONTYPES; k++)
				field[i][j][k] = 0;*/
	if(numberOfSources != 0) {
		delete [] sources;
	}
	numberOfSources = 0;
};