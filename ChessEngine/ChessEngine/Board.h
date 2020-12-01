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

	//return true if the piece has been succesfully moved 
	bool movePiece(const Coordinate& origin, const Coordinate& target) 
	{
		if (origin == target) return false;

		Piece* piece = getPieceAt(origin);
		if (piece != NULL) 
		{
			//set the origin to NULL
			setPieceAt(origin, NULL);

			//set the piece to the new location
			setPieceAt(target, piece);

			//update the piece's coordinate history
			piece->addCoordinateToHistory(target);

			return true;
		}

		return false;
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

	bool isCoordinateValid(const Coordinate& coordinate) const
	{
		//Boundary checking
		if (coordinate.getX() < 0 || coordinate.getX() >= SIZE_X) return false;
		if (coordinate.getY() < 0 || coordinate.getY() >= SIZE_Y) return false;

		return true;
	}
	
	//Loading function receives a new set, or existing set
	void load(IBoardPopulator* populator) 
	{
		populator->populate(*this);
	}	

	int getSizeX() const
	{
		return SIZE_X;
	}
	int getSizeY() const
	{
		return SIZE_Y;
	}

	void print() 
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			for (int i = 0; i < SIZE_X; i++)
			{
				int id = 0;
				Piece* p = getPieceAt(Coordinate(i, j));
				if (p) id = p->getID();

				std::cout << id << ", ";	
			}

			std::cout << std::endl;
		}	
	}

	Piece* getPieceAt(const Coordinate& coordinate) const
	{
		if (!isCoordinateValid(coordinate)) return NULL;

		return matrix[coordinate.getX()][coordinate.getY()];
	}

	void setPieceAt(const Coordinate& coordinate, Piece* piece)
	{
		if (!isCoordinateValid(coordinate)) return;

		matrix[coordinate.getX()][coordinate.getY()] = piece;
	}

private:
	const int SIZE_X = 8;
	const int SIZE_Y = 8;

	std::vector<std::vector<Piece*>> matrix;
};