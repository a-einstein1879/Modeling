#ifndef COORDINATES_H
#define COORDINATES_H

struct Direction {
	double fi;
};

//TODO:Better remove extern function as soon as it`s possible. just move it to environment class
extern void getTwoDirections(struct Direction direction, struct Direction *twoDirections);

class Coordinates {
private:
   int CoordX;
   int CoordY;
public:
	Coordinates& operator=( Coordinates &coord );
	void PrintCoordinates();
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	double findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId); // Helps neurite to find new coordinates
};

#endif