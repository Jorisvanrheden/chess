#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(const PLAYER_TYPE& type) : Piece(type) {}
	~Rook() {}

	PIECE_TYPE getID()
	{
		return PIECE_TYPE::ROOK;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A rook traverses the horizontal and verticals (with unlimited range)
		//the first obstacle it encounters in any diagonal defines the limit
		std::vector<Coordinate> moves;
	
		getMovesInDirection(moves, board, coordinate, Direction(1, 0));
		getMovesInDirection(moves, board, coordinate, Direction(-1, 0));
		getMovesInDirection(moves, board, coordinate, Direction(0, 1));
		getMovesInDirection(moves, board, coordinate, Direction(0, -1));

		return moves;
	}
};