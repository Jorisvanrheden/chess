#pragma once

#include "IMoveHandler.h"

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
};