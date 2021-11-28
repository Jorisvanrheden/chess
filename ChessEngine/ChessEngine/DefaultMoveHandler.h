#pragma once

#include "IMoveHandler.h"

#include "MoveSet.h"

class DefaultMoveHandler : public IMoveHandler
{
public:
	MoveSet* getMoveSet(Board& board, const Coordinate& origin, const Coordinate& target)
	{
		Piece* piece = board.getPieceAt(origin);

		//if the piece is a king, and the selected target is part of the castling routine
		//then return a multiple moveset
		if (piece->getID() == PIECE_TYPE::KING) 
		{
			King* king = (King*)piece;

			MoveSet* castleMoveSet = king->combination->getCastlingMoveSet(board, target);
			if (castleMoveSet) return castleMoveSet;
		}

        std::vector<MoveContent> content;
        //TODO: fix this NULL
        content.push_back(MoveContent(piece, origin, target, {}));

		//otherwise return a single moveset
		return new MoveSet(content);
	}
};