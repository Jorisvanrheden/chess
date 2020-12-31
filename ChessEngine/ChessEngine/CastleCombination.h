#pragma once

#include "Piece.h"
#include "MoveSetMultiple.h"
#include "PieceCheckDetector.h"

class CastleCombination
{
public:
	CastleCombination(Piece* king, Piece* rook_short, Piece* rook_long) 
		: king(king), rook_short(rook_short), rook_long(rook_long)
	{
	}
	~CastleCombination() {}

	IMoveSet* getMoveSetShortCastle() 
	{
		return getMoveSet(rook_short);
	}

	IMoveSet* getMoveSetLongCastle()
	{
		return getMoveSet(rook_long);
	}

	std::vector<Coordinate> getInitiatingMoves(const Board& board)
	{
		std::vector<Coordinate> moves;

		//No possibility for castling if the king already moved before
		if (king->getMoveCount() > 1) return moves;

		//No possibility for castling if the king is checked
		//PieceCheckDetector checkDetector(king->getID());
		//if (checkDetector.isChecked(board, king->getPlayerType())) return moves;

		if (checkIfCastlingPossible(board, rook_short))
		{
			moves.push_back(getKingTargetLocation(rook_short));
		}

		if (checkIfCastlingPossible(board, rook_long))
		{
			moves.push_back(getKingTargetLocation(rook_long));
		}

		return moves;
	}

	IMoveSet* getCastlingMoveSet(const Board& board, const Coordinate& target) 
	{
		if (checkIfCastlingPossible(board, rook_short))
		{
			if (getKingTargetLocation(rook_short) == target) 
			{
				return getMoveSet(rook_short);
			}
		}

		if (checkIfCastlingPossible(board, rook_long))
		{
			if (getKingTargetLocation(rook_long) == target)
			{
				return getMoveSet(rook_long);
			}
		}

		return NULL;
	}

private:
	Piece* king;
	Piece* rook_short;
	Piece* rook_long;

	const int CASTLE_KING_STEPS = 2;

	bool checkIfCastlingPossible(const Board& board, Piece* activeRook) 
	{
		if (activeRook->getMoveCount() != 1) return false;

		Direction dir(activeRook->getCurrentCoordinate().getX() - king->getCurrentCoordinate().getX(),
					  activeRook->getCurrentCoordinate().getY() - king->getCurrentCoordinate().getY());

		//loop through all spaces between the king and the active rook
		//if there is still a piece, castling is not possible
		int xDiff = abs(king->getCurrentCoordinate().getX() - activeRook->getCurrentCoordinate().getX());
		int yDiff = abs(king->getCurrentCoordinate().getY() - activeRook->getCurrentCoordinate().getY());

		for (int i = 1; i < xDiff; i++)
		{
			int distanceX = i * dir.getX();
			int distanceY = i * dir.getY();

			Coordinate coord(king->getCurrentCoordinate().getX() + distanceX, king->getCurrentCoordinate().getY() + distanceY);
			Piece* piece = board.getPieceAt(coord);
			if (piece) return false;
		}

		return true;
	}

	Coordinate getKingTargetLocation(Piece* activeRook)
	{
		Direction dir(activeRook->getCurrentCoordinate().getX() - king->getCurrentCoordinate().getX(),
					  activeRook->getCurrentCoordinate().getY() - king->getCurrentCoordinate().getY());

		Coordinate kingTarget(king->getCurrentCoordinate().getX() + dir.getX() * CASTLE_KING_STEPS, king->getCurrentCoordinate().getY());

		return kingTarget;
	}

	IMoveSet* getMoveSet(Piece* activeRook) 
	{
		std::vector<std::tuple<Coordinate, Coordinate>> moves;

		Direction dir(activeRook->getCurrentCoordinate().getX() - king->getCurrentCoordinate().getX(),
					  activeRook->getCurrentCoordinate().getY() - king->getCurrentCoordinate().getY());

		Coordinate kingOrigin(king->getCurrentCoordinate().getX(), king->getCurrentCoordinate().getY());
		Coordinate kingTarget(king->getCurrentCoordinate().getX() + dir.getX() * CASTLE_KING_STEPS, king->getCurrentCoordinate().getY());

		Coordinate rookOrigin(activeRook->getCurrentCoordinate().getX(), activeRook->getCurrentCoordinate().getY());
		Coordinate rookTarget(kingTarget.getX() + dir.getX() * -1, activeRook->getCurrentCoordinate().getY());

		moves.push_back(std::tuple<Coordinate, Coordinate>{kingOrigin, kingTarget});
		moves.push_back(std::tuple<Coordinate, Coordinate>{rookOrigin, rookTarget});

		return new MoveSetMultiple(moves);
	}
};