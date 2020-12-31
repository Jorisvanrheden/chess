#pragma once

#include "IMoveHandler.h"

#include "MoveSetSingle.h"

class DefaultMoveHandler : public IMoveHandler
{
public:
	void movePiece(Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
		//set the origin to NULL
		board.setPieceAt(origin, NULL);

		//set the piece to the new location
		board.setPieceAt(target, piece);		
	}

	IMoveSet* getMoveSet(Board& board, const Coordinate& origin, const Coordinate& target)
	{
		Piece* piece = board.getPieceAt(origin);

		//if the piece is a king, and the selected target is part of the castling routine
		//then return a multiple moveset
		if (piece->getID() == PIECE_TYPE::KING) 
		{
			King* king = (King*)piece;

			IMoveSet* castleMoveSet = king->combination->getCastlingMoveSet(board, target);
			if (castleMoveSet) return castleMoveSet;
		}

		//otherwise return a single moveset
		return new MoveSetSingle(origin, target);
	}
};