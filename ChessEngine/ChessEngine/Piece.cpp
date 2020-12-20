#include "Piece.h"
#include "Board.h"

#include "ISpecialMove.h"

Piece::Piece(const PLAYER_TYPE& type)
	: type(type)
{
}

void Piece::getMovesInDirection(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit, bool includeHit)
{
	int iteration = 0;

	while (true) 
	{
		//only if a limit is used, perform the limit to iteration check
		if (limit != -1)
		{
			if (iteration >= limit) return;
		}

		//prepare the coordinate for the next iteration, because the input coordinate is the location of the piece
		coordinate = Coordinate(coordinate.getX() + direction.getX(), coordinate.getY() + direction.getY());

		//check if the updated coordinate is still within bounds
		if (!board.isCoordinateValid(coordinate)) return;

		//if a piece is encountered, resolve
		Piece* obstacle = board.getPieceAt(coordinate);

		if (obstacle == NULL) moves.push_back(coordinate);
		else 
		{
			//only if the piece is specified to include a 'hitting piece' should it be added
			if (includeHit) moves.push_back(coordinate);
		}

		if (obstacle != NULL)
		{
			//any obstacle will be added to the set of available moves but stops any continuation in that direction						
			//the board will later verify whether those moves are valid (e.g. moving to a piece of the same type is not allowed)
			return;
		}

		iteration++;
	}	
}

void Piece::addTest(const Board& board, std::vector<Coordinate>& moves)
{
	//also find raw special moves?
	for (int i = 0; i < specialMoves.size(); i++)
	{
		std::vector<Coordinate> sMoves = specialMoves[i]->getInitiatingMoves(board);
		for (const auto& m : sMoves)
		{
			moves.push_back(m);
		}
	}
}
