#pragma once

#include "Piece.h"
#include "PieceCheckDetector.h"
#include "SquareAttackDetector.h"

class CastleCombination
{
public:
	CastleCombination(Piece* king, Piece* rook_short, Piece* rook_long) 
		: king(king), rook_short(rook_short), rook_long(rook_long)
	{
	}
	~CastleCombination() {}

	MoveSet* getMoveSetShortCastle() 
	{
		return getMoveSet(rook_short);
	}

	MoveSet* getMoveSetLongCastle()
	{
		return getMoveSet(rook_long);
	}

	std::vector<Coordinate> getInitiatingMoves(const Board& board)
	{
		std::vector<Coordinate> moves;

        //Castling is not possible in the following cases:
        //1.) King has moved already
        //2.) King is in check
        //3.) Rook to castle with has moved already
        //4.) End position of castling brings the king in check
        //5.) In-between squares of castling brings the king in check
        //6.) A piece is in between the king and rook

        //1.) King has moved already
        if (king->getMoveCount() > 1) return moves;

        //2.) King is in check
        PieceCheckDetector checkDetector(king->getID());
        if (checkDetector.isChecked(board, king->getPlayerType())) return moves;

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

	MoveSet* getCastlingMoveSet(const Board& board, const Coordinate& target) 
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
        //3.) Rook to castle with has moved already
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

			Coordinate coordinate(king->getCurrentCoordinate().getX() + distanceX, king->getCurrentCoordinate().getY() + distanceY);

            //4.) End position of castling brings the king in check
            //5.) In-between squares of castling brings the king in check
            SqaureAttackDetector attackDetector;
            if (attackDetector.isAttacked(board, coordinate, king->getPlayerType())) return false;

            //6.) A piece is in between the king and rook
            Piece* piece = board.getPieceAt(coordinate);
            if (piece != NULL) return false;
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

	MoveSet* getMoveSet(Piece* activeRook) 
	{
		Direction dir(activeRook->getCurrentCoordinate().getX() - king->getCurrentCoordinate().getX(),
					  activeRook->getCurrentCoordinate().getY() - king->getCurrentCoordinate().getY());

		Coordinate kingOrigin(king->getCurrentCoordinate().getX(), king->getCurrentCoordinate().getY());
		Coordinate kingTarget(king->getCurrentCoordinate().getX() + dir.getX() * CASTLE_KING_STEPS, king->getCurrentCoordinate().getY());

		Coordinate rookOrigin(activeRook->getCurrentCoordinate().getX(), activeRook->getCurrentCoordinate().getY());
		Coordinate rookTarget(kingTarget.getX() + dir.getX() * -1, activeRook->getCurrentCoordinate().getY());

        std::vector<MoveContent> content;
        content.push_back(MoveContent(king, kingOrigin, kingTarget, {}));
        content.push_back(MoveContent(king, rookOrigin, rookTarget, {}));

        return new MoveSet(content);
	}
};