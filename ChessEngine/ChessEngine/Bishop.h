#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const PlayerType& type) : Piece(type) {}
	~Bishop() {}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A bishop traverses the diagonals (with unlimited range)
		//the first obstacle it encounters in any diagonal defines the limit
		std::vector<Coordinate> moves;

		addMoves(moves, board, coordinate, coordinate, 1, 1);
		addMoves(moves, board, coordinate, coordinate, -1, 1);
		addMoves(moves, board, coordinate, coordinate, 1, -1);
		addMoves(moves, board, coordinate, coordinate, -1, -1);

		return moves;
	}

	void addMoves(std::vector<Coordinate>& moves, const Board& board, const Coordinate& coordinate, Coordinate nextCoordinate, int xDir, int yDir)
	{
		if (coordinate.getX() != nextCoordinate.getX() && coordinate.getY() != nextCoordinate.getY()) 
		{
			//check if the updated coordinate is still within bounds
			if (!board.isCoordinateValid(nextCoordinate)) return;

			//if a piece is encountered, resolve
			Piece* obstacle = board.getPieceAt(nextCoordinate);
			if (obstacle != NULL)
			{
				//if the obstacle is a different type, the coordinate is allowed, 
				//but stops any continuation in that direction
				if (!obstacle->isSameType(this))
				{
					moves.push_back(nextCoordinate);
					return;
				}
				else 
				{
					return;
				}
			}

			moves.push_back(nextCoordinate);
		}

		addMoves(moves, board, coordinate, Coordinate(nextCoordinate.getX() + xDir, nextCoordinate.getY() + yDir), xDir, yDir);
	}
};