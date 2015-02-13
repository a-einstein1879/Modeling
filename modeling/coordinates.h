#ifndef COORDINATES_H
#define COORDINATES_H

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
};

#endif