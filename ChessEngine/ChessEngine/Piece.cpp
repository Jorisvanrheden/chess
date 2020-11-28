#include "Piece.h"
#include "Board.h"

Piece::Piece(const PlayerType& type)
	: type(type)
{
}

void Piece::getDirectionalMoves(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit, int iteration)
{
	//only if a limit is used, perform the limit to iteration check
	if (limit != -1)
	{
		if (iteration >= limit) return;
	}

	if (iteration > 0)
	{
		//check if the updated coordinate is still within bounds
		if (!board.isCoordinateValid(coordinate)) return;

		//if a piece is encountered, resolve
		Piece* obstacle = board.getPieceAt(coordinate);
		if (obstacle != NULL)
		{
			//if the obstacle is a different type, the coordinate is allowed, 
			//but stops any continuation in that direction
			if (!obstacle->isSameType(this))
			{
				moves.push_back(coordinate);
				return;
			}
			else
			{
				return;
			}
		}

		moves.push_back(coordinate);
	}

	//prepare the coordinate for the next iteration
	Coordinate nextCoordinate(coordinate.getX() + direction.getX(), coordinate.getY() + direction.getY());

	//perform next iteration
	getDirectionalMoves(moves, board, nextCoordinate, direction, limit, iteration + 1);
}
