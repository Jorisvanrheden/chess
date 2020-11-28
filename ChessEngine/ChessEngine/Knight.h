#pragma once
#include "Piece.h"

class Knight : public Piece 
{
public:
	Knight(const PlayerType& type) : Piece(type) {}
	~Knight() {}

	int getID()
	{
		return 2;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A Knight has a range of 5x5 (given that the knight is the center coordinate)
		
		//The move is built up in two separate steps:
		//- move North, East, South or West
		//- move one unit perpendicular to the previous move 
		std::vector<Coordinate> moves;

		addMovesToCollection(moves, getMovesPerDirection(coordinate, Direction(0, 1)));
		addMovesToCollection(moves, getMovesPerDirection(coordinate, Direction(0, -1)));
		addMovesToCollection(moves, getMovesPerDirection(coordinate, Direction(1, 0)));
		addMovesToCollection(moves, getMovesPerDirection(coordinate, Direction(-1, 0)));

		return moves;
	}

	void addMovesToCollection(std::vector<Coordinate>& moves, std::vector<Coordinate> newMoves) 
	{
		moves.insert(moves.end(), newMoves.begin(), newMoves.end());
	}

	std::vector<Coordinate> getMovesPerDirection(const Coordinate& coordinate, const Direction& direction) 
	{
		const int BASE_MOVE_DISTANCE = 2;

		std::vector<Coordinate> moves;

		int xAddition = direction.getX() * BASE_MOVE_DISTANCE;
		int yAddition = direction.getY() * BASE_MOVE_DISTANCE;

		if (direction.getY() == 0)
		{
			//Add top and bottom
			moves.push_back(Coordinate(coordinate.getX() + xAddition, coordinate.getY() + 1));
			moves.push_back(Coordinate(coordinate.getX() + xAddition, coordinate.getY() - 1));
		}
		else if (direction.getX() == 0)
		{
			//Add right and left
			moves.push_back(Coordinate(coordinate.getX() + 1, coordinate.getY() + yAddition));
			moves.push_back(Coordinate(coordinate.getX() - 1, coordinate.getY() + yAddition));
		}

		return moves;
	}
};