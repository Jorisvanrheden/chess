#pragma once

#include "ISpecialMove.h"
#include "Piece.h"
#include "MoveSetMultiple.h"
#include "PieceCheckDetector.h"

class CastleCombination : public ISpecialMove
{
public:
	CastleCombination(Piece* king, Piece* rook_short, Piece* rook_long) 
		: king(king), rook_short(rook_short), rook_long(rook_long)
	{
	}
	~CastleCombination() {}

	IMoveSet* getMove(const std::string& moveString, PLAYER_TYPE type) 
	{
		if (moveString != CASTLE_SHORT && moveString != CASTLE_LONG) return NULL;

		if (king == NULL)return NULL;
		if (king->getPlayerType() != type)return NULL;

		Piece* activeRook = NULL;

		if (moveString == CASTLE_SHORT)
		{
			activeRook = rook_short;
		}
		else if (moveString == CASTLE_LONG)
		{
			activeRook = rook_long;
		}

		std::vector<std::tuple<Coordinate, Coordinate>> multipleMoves;

		Direction dir(activeRook->getCurrentCoordinate().getX() - king->getCurrentCoordinate().getX(), 
					  activeRook->getCurrentCoordinate().getY() - king->getCurrentCoordinate().getY());

		Coordinate kingOrigin(king->getCurrentCoordinate().getX(), king->getCurrentCoordinate().getY());
		Coordinate kingTarget(king->getCurrentCoordinate().getX() + dir.getX() * CASTLE_KING_STEPS, king->getCurrentCoordinate().getY());

		Coordinate rookOrigin(activeRook->getCurrentCoordinate().getX(), activeRook->getCurrentCoordinate().getY());
		Coordinate rookTarget(kingTarget.getX() + dir.getX() * -1, activeRook->getCurrentCoordinate().getY());

		multipleMoves.push_back(std::tuple<Coordinate, Coordinate>{kingOrigin, kingTarget});
		multipleMoves.push_back(std::tuple<Coordinate, Coordinate>{rookOrigin, rookTarget});

		return new MoveSetMultiple(multipleMoves);
	}

	bool isRelevantPiece(Piece* piece) 
	{
		return piece == king;
	}

	std::vector<Coordinate> getInitiatingMoves(const Board& board)
	{
		std::vector<Coordinate> moves;

		//No possibility for castling if the king already moved before
		if (king->getMoveCount() > 1) return moves;

		//No possibility for castling if the king is checked
		PieceCheckDetector checkDetector(king->getID());
		if (checkDetector.isChecked(board, king->getPlayerType())) return moves;

		if (rook_short->getMoveCount() == 1) 
		{
			moves.push_back(getKingTargetLocation(rook_short));
		}

		if (rook_long->getMoveCount() == 1) 
		{
			moves.push_back(getKingTargetLocation(rook_long));
		}

		return moves;
	}

private:
	Piece* king;
	Piece* rook_short;
	Piece* rook_long;

	const int CASTLE_KING_STEPS = 2;
	const std::string CASTLE_SHORT = "O-O";
	const std::string CASTLE_LONG = "O-O-O";

	Coordinate getKingTargetLocation(Piece* activeRook)
	{
		Direction dir(activeRook->getCurrentCoordinate().getX() - king->getCurrentCoordinate().getX(),
					  activeRook->getCurrentCoordinate().getY() - king->getCurrentCoordinate().getY());

		Coordinate kingTarget(king->getCurrentCoordinate().getX() + dir.getX() * CASTLE_KING_STEPS, king->getCurrentCoordinate().getY());

		return kingTarget;
	}
};