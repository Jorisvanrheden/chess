#pragma once

#include <malloc.h>
#include <iostream>
#include "Piece.h"
#include "IBoardPopulator.h"

class Board
{
public:
	Board() 
	{
		//init empty board
		matrix = std::vector<std::vector<Piece*>>(SIZE_X);
		for (int i = 0; i < SIZE_X; i++)
		{
			std::vector<Piece*> row(SIZE_Y);

			matrix[i] = row;
		}
	}
	~Board() {}

	void setPieceAt(const Coordinate& coordinate, Piece* piece) 
	{
		if (!isCoordinateValid(coordinate)) return;

		matrix[coordinate.getX()][coordinate.getY()] = piece;
	}

	Piece* getPieceAt(const Coordinate& coordinate)
	{
		if (!isCoordinateValid(coordinate)) return NULL;

		return matrix[coordinate.getX()][coordinate.getY()];
	}

	//Loading function receives a new set, or existing set
	void load(IBoardPopulator* populator) 
	{
		populator->populate(*this);
	}

	bool isCoordinateValid(const Coordinate& coordinate) 
	{
		//Boundary checking
		if (coordinate.getX() < 0 || coordinate.getX() >= SIZE_X) return false;
		if (coordinate.getY() < 0 || coordinate.getY() >= SIZE_Y) return false;

		return true;
	}

	int getSizeX() 
	{
		return SIZE_X;
	}
	int getSizeY() 
	{
		return SIZE_Y;
	}

private:
	const int SIZE_X = 8;
	const int SIZE_Y = 8;

	std::vector<std::vector<Piece*>> matrix;
};