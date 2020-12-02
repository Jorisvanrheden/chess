#include "Piece.h"
#include "Board.h"

Piece::Piece(const PLAYER_TYPE& type)
	: type(type)
{
}

void Piece::getDirectionalUnits(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit, int iteration) 
{
	//only if a limit is used, perform the limit to iteration check
	if (limit != -1)
	{
		if (iteration > limit) return;
	}

	if (iteration > 0)
	{
		//check if the updated coordinate is still within bounds
		if (!board.isCoordinateValid(coordinate)) return;

		//if a piece is encountered, resolve
		Piece* obstacle = board.getPieceAt(coordinate);
		if (obstacle != NULL)
		{
			//any obstacle will be added to the set of available moves but stops any continuation in that direction						
			//the board will later verify whether those moves are valid (e.g. moving to a piece of the same type is not allowed)

			moves.push_back(coordinate);

			return;
		}
	}

	//prepare the coordinate for the next iteration
	Coordinate nextCoordinate(coordinate.getX() + direction.getX(), coordinate.getY() + direction.getY());

	//perform next iteration
	getDirectionalUnits(moves, board, nextCoordinate, direction, limit, iteration + 1);
}

void Piece::getDirectionalMoves(std::vector<Coordinate>& moves, const Board& board, Coordinate coordinate, const Direction& direction, int limit, int iteration)
{
	//only if a limit is used, perform the limit to iteration check
	if (limit != -1)
	{
		if (iteration > limit) return;
	}

	if (iteration > 0)
	{
		//check if the updated coordinate is still within bounds
		if (!board.isCoordinateValid(coordinate)) return;

		moves.push_back(coordinate);

		//if a piece is encountered, resolve
		Piece* obstacle = board.getPieceAt(coordinate);
		if (obstacle != NULL)
		{
			//any obstacle will be added to the set of available moves but stops any continuation in that direction						
			//the board will later verify whether those moves are valid (e.g. moving to a piece of the same type is not allowed)
			return;
		}
	}

	//prepare the coordinate for the next iteration
	Coordinate nextCoordinate(coordinate.getX() + direction.getX(), coordinate.getY() + direction.getY());

	//perform next iteration
	getDirectionalMoves(moves, board, nextCoordinate, direction, limit, iteration + 1);
}
