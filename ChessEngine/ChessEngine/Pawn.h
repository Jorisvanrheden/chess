#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const PLAYER_TYPE& type) : Piece(type) {}
	~Pawn() {}

	int getID()
	{
		return 1;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A pawn can only move up or down (depending on it's type)
		std::vector<Coordinate> moves;

		Direction direction(0, 1);
		
		switch (type)
		{
		case PLAYER_TYPE::BLACK:
			direction = Direction(0, 1);
			break;
		case PLAYER_TYPE::WHITE:
			direction = Direction(0, -1);
			break;
		default:
			break;
		}

		//pawns are different in the sense that their movement vector does not equal the attack vector
		//they move only up and down, but attack diagonally
		//there both types of moves should be included in the available move set

		//pawns can move 2 units in a straight direction if they haven't been moved yet
		int moveDistance = (coordinateHistory.size() > 0) ? 1 : 2;
		getDirectionalMoves(moves, board, coordinate, direction, moveDistance);

		//pawn can attack diagonally, but only with a distance of 1
		getDirectionalUnits(moves, board, coordinate, Direction(1, direction.getY()), 1);
		getDirectionalUnits(moves, board, coordinate, Direction(-1, direction.getY()), 1);

		return moves;
	}
};