#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const PLAYER_TYPE& type) : Piece(type) {}
	~Queen() {}
	
	PIECE_TYPE getID()
	{
		return PIECE_TYPE::QUEEN;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A rook traverses the horizontal and verticals (with unlimited range)
		//the first obstacle it encounters in any diagonal defines the limit
		std::vector<Coordinate> moves;

		//horizontal and vertical
		getMovesInDirection(moves, board, coordinate, Direction(1, 0));
		getMovesInDirection(moves, board, coordinate, Direction(-1, 0));
		getMovesInDirection(moves, board, coordinate, Direction(0, 1));
		getMovesInDirection(moves, board, coordinate, Direction(0, -1));

		//diagonal
		getMovesInDirection(moves, board, coordinate, Direction(1, 1));
		getMovesInDirection(moves, board, coordinate, Direction(-1, 1));
		getMovesInDirection(moves, board, coordinate, Direction(1, -1));
		getMovesInDirection(moves, board, coordinate, Direction(-1, -1));

		return moves;
	}
};