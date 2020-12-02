#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(const PLAYER_TYPE& type) : Piece(type) {}
	~Rook() {}

	int getID()
	{
		return 4;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A rook traverses the horizontal and verticals (with unlimited range)
		//the first obstacle it encounters in any diagonal defines the limit
		std::vector<Coordinate> moves;
	
		getDirectionalMoves(moves, board, coordinate, Direction(1, 0));
		getDirectionalMoves(moves, board, coordinate, Direction(-1, 0));
		getDirectionalMoves(moves, board, coordinate, Direction(0, 1));
		getDirectionalMoves(moves, board, coordinate, Direction(0, -1));

		return moves;
	}
};