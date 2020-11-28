#pragma once
#include <iostream>
#include "Piece.h"

class Knight : public Piece 
{
public:
	Knight(const PlayerType& type) : Piece(type) {}
	~Knight() {}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A Knight has a range of 5x5 (given that the knight is the center coordinate)
		
		//The move is built up in two separate steps:
		//- move North, East, South or West
		//- move one unit perpendicular to the previous move 
		std::vector<Coordinate> moves;

		std::vector<Coordinate> rawMoves;
		addMovesToCollection(rawMoves, getMovesPerDirection(coordinate, 0, 1));
		addMovesToCollection(rawMoves, getMovesPerDirection(coordinate, 0, -1));
		addMovesToCollection(rawMoves, getMovesPerDirection(coordinate, 1, 0));
		addMovesToCollection(rawMoves, getMovesPerDirection(coordinate, -1, 0));

		return moves;
	}

	void addMovesToCollection(std::vector<Coordinate>& moves, std::vector<Coordinate> newMoves) 
	{
		moves.insert(moves.end(), newMoves.begin(), newMoves.end());
	}

	std::vector<Coordinate> getMovesPerDirection(const Coordinate& coordinate, int xDir, int yDir) 
	{
		const int BASE_MOVE_DISTANCE = 2;

		std::vector<Coordinate> moves;

		int xAddition = xDir * BASE_MOVE_DISTANCE;
		int yAddition = yDir * BASE_MOVE_DISTANCE;

		if (xDir == 0) 
		{
			//Add top and bottom
			moves.push_back(Coordinate(coordinate.getX() + xAddition, coordinate.getY() + 1));
			moves.push_back(Coordinate(coordinate.getX() + xAddition, coordinate.getY() - 1));
		}
		else if (yDir == 0) 
		{
			//Add right and left
			moves.push_back(Coordinate(coordinate.getX() + 1, coordinate.getY() + yAddition));
			moves.push_back(Coordinate(coordinate.getX() - 1, coordinate.getY() + yAddition));
		}

		return moves;
	}
};