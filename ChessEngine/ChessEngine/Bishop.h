#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const PLAYER_TYPE& type) : Piece(type) {}
	~Bishop() {}

	int getID()
	{
		return 3;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A bishop traverses the diagonals (with unlimited range)
		//the first obstacle it encounters in any diagonal defines the limit
		std::vector<Coordinate> moves;

		getDirectionalMoves(moves, board, coordinate, Direction(1, 1));
		getDirectionalMoves(moves, board, coordinate, Direction(-1, 1));
		getDirectionalMoves(moves, board, coordinate, Direction(1, -1));
		getDirectionalMoves(moves, board, coordinate, Direction(-1, -1));

		return moves;
	}
};