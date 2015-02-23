#ifndef COORDINATES_H
#define COORDINATES_H

struct Direction {
	double fi;
};

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
	void findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId); // Helps neurite to find new coordinates
};

#endif