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

	std::vector<Coordinate> getAvailableMoves(const Coordinate& coordinate) 
	{
		Piece* piece = getPieceAt(coordinate);
		if (piece == NULL) return std::vector<Coordinate>();

		std::vector<Coordinate> rawMoves = piece->findAvailableMoves(coordinate, *this);
		return getValidatedMoves(piece, rawMoves);
	}

	std::vector<Coordinate> getValidatedMoves(Piece* piece, std::vector<Coordinate> moves) 
	{
		std::vector<Coordinate> validatedMoves;

		for (int i = 0; i < moves.size(); i++) 
		{
			if (isMoveValid(piece, moves[i])) validatedMoves.push_back(moves[i]);
		}

		return validatedMoves;
	}
	
	//Loading function receives a new set, or existing set
	void load(IBoardPopulator* populator) 
	{
		populator->populate(*this);
	}

	bool isMoveValid(Piece* piece, const Coordinate& coordinate)
	{
		//make sure the coordinate is within the board
		if (!isCoordinateValid(coordinate)) return false;

		//check if there is already a piece on the target position
		//- if there is already a piece, it can only be of a different playertype (as own pieces cannot be consumed)
		Piece* targetedPiece = getPieceAt(coordinate);
		if (targetedPiece != NULL) 
		{
			if (targetedPiece->isSameType(piece)) return false;
		}

		return true;
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