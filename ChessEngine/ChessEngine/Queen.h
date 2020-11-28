#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const PlayerType& type) : Piece(type) {}
	~Queen() {}
	
	int getID()
	{
		return 5;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A rook traverses the horizontal and verticals (with unlimited range)
		//the first obstacle it encounters in any diagonal defines the limit
		std::vector<Coordinate> moves;

		//horizontal and vertical
		getDirectionalMoves(moves, board, coordinate, Direction(1, 0));
		getDirectionalMoves(moves, board, coordinate, Direction(-1, 0));
		getDirectionalMoves(moves, board, coordinate, Direction(0, 1));
		getDirectionalMoves(moves, board, coordinate, Direction(0, -1));

		//diagonal
		getDirectionalMoves(moves, board, coordinate, Direction(1, 1));
		getDirectionalMoves(moves, board, coordinate, Direction(-1, 1));
		getDirectionalMoves(moves, board, coordinate, Direction(1, -1));
		getDirectionalMoves(moves, board, coordinate, Direction(-1, -1));

		return moves;
	}
};