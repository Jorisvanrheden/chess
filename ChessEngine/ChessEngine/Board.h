#pragma once

#include <malloc.h>
#include <iostream>
#include "Piece.h"

#include "MoveValidationManager.h"
#include "IMoveHandler.h"
#include "ISpecification.h"
#include "IFilter.h"

class Board
{
public:
	Board(MoveValidationManager* validationManager, IMoveHandler* moveHandler, IFilter<Piece>* pieceFilter) 
		: validationManager(validationManager), moveHandler(moveHandler), pieceFilter(pieceFilter)
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
			moveHandler->movePiece(*this, piece, origin, target);		

			return true;
		}

		return false;
	}

	std::vector<Coordinate> getAvailableMoves(const Coordinate& origin) 
	{
		Piece* piece = getPieceAt(origin);
		if (piece == NULL) return std::vector<Coordinate>();

		std::vector<Coordinate> rawMoves = piece->findAvailableMoves(origin, *this);
		std::vector<Coordinate> boundaryValidatedMoves = getBoundaryValidatedMoves(origin, piece, rawMoves);
		std::vector<Coordinate> logicValidatedMoves = getLogicValidatedMoves(origin, piece, boundaryValidatedMoves);

		return logicValidatedMoves;
	}

	std::vector<Coordinate> getPieceBoundaryValidatedMoves(Piece* piece) 
	{
		Coordinate origin = piece->getCurrentCoordinate();
		std::vector<Coordinate> rawMoves = piece->findAvailableMoves(origin, *this);
		std::vector<Coordinate> boundaryValidatedMoves = getBoundaryValidatedMoves(origin, piece, rawMoves);

		return boundaryValidatedMoves;
	}

	std::vector<Coordinate> getBoundaryValidatedMoves(const Coordinate& origin, Piece* piece, std::vector<Coordinate> moves) 
	{
		std::vector<Coordinate> validatedMoves;

		for (int i = 0; i < moves.size(); i++)
		{
			//make sure the coordinate is within the board
			if (!isCoordinateValid(moves[i])) continue;

			validatedMoves.push_back(moves[i]);
		}

		return validatedMoves;
	}

	std::vector<Coordinate> getLogicValidatedMoves(const Coordinate& origin, Piece* piece, std::vector<Coordinate> moves)
	{
		std::vector<Coordinate> validatedMoves;

		for (int i = 0; i < moves.size(); i++)
		{
			if (validationManager->isMoveValid(*this, piece, origin, moves[i])) 
			{
				validatedMoves.push_back(moves[i]);
			}
		}

		return validatedMoves;
	}

	bool isCoordinateValid(const Coordinate& coordinate) const
	{
		//Boundary checking
		if (coordinate.getX() < 0 || coordinate.getX() >= SIZE_X) return false;
		if (coordinate.getY() < 0 || coordinate.getY() >= SIZE_Y) return false;

		return true;
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

	std::vector<Piece*> filter(ISpecification<Piece>& specification) 
	{
		return pieceFilter->filter(getAllPieces(), specification);
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

		//Not sure if I want this to be done here.
		//Also check whether it makes sense to have this coordinate history list per piece?
		if (piece != NULL)
		{
			//update the piece's coordinate history
			piece->addCoordinateToHistory(coordinate);
		}
	}

private:
	const int SIZE_X = 8;
	const int SIZE_Y = 8;

	IFilter<Piece>* pieceFilter;
	IMoveHandler* moveHandler;
	MoveValidationManager* validationManager;

	std::vector<std::vector<Piece*>> matrix;

	std::vector<Piece*> getAllPieces() 
	{
		std::vector<Piece*> pieces;

		for (int j = 0; j < SIZE_Y; j++)
		{
			for (int i = 0; i < SIZE_X; i++)
			{
				Piece* piece = getPieceAt(Coordinate(i, j));
				if (piece) pieces.push_back(piece);
			}
		}

		return pieces;
	}
};