#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const PLAYER_TYPE& type, Direction direction) 
		: Piece(type), direction(direction) 
	{}
	~Pawn() {}

	PIECE_TYPE getID()
	{
		return PIECE_TYPE::PAWN;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A pawn can only move up or down (depending on it's type)
		std::vector<Coordinate> moves;

		//pawns are different in the sense that their movement vector does not equal the attack vector
		//they move only up and down, but attack diagonally
		//there both types of moves should be included in the available move set

		//pawns can move 2 units in a straight direction if they haven't been moved yet
		int moveDistance = (coordinateHistory.size() > 1) ? 1 : 2;
		getMovesInDirection(moves, board, coordinate, direction, moveDistance, false);

		//pawns can attack diagonally, but only with a distance of 1
		//to the the diagonal, we get the perpendicular directions
		std::vector<Direction> perpendicularDirections = getPerpendicularDirections(direction);
		for (auto& perpendicular : perpendicularDirections)
		{
			//also add the direction for one unit, otherwise we'd be checking next to the pawn, not diagonally
			int x = coordinate.getX() + direction.getX() + perpendicular.getX();
			int y = coordinate.getY() + direction.getY() + perpendicular.getY();

			Coordinate targetCoordinate(x, y);
			Piece* targetPiece = board.getPieceAt(targetCoordinate);

			if (targetPiece) 
			{
				moves.push_back(targetCoordinate);
			}
		}

		return moves;
	}

	std::vector<Direction> getPerpendicularDirections(const Direction& direction) 
	{
		std::vector<Direction> directions;

		//clockwise
		directions.push_back(Direction(direction.getY(), -direction.getX()));

		//counter clockwise
		directions.push_back(Direction(-direction.getY(), direction.getX()));

		return directions;
	}

private:
	Direction& direction;
};