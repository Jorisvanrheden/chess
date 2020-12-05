#pragma once

#include "IMoveValidator.h"

class FriendlyFireValidator : public IMoveValidator
{
	bool isMoveValid(const Board& board, Piece* piece, const Coordinate& coordinate)
	{
		//check if there is already a piece on the target position
		//- if there is already a piece, it can only be of a different PLAYER_TYPE (as own pieces cannot be consumed)
		Piece* targetedPiece = board.getPieceAt(coordinate);
		if (targetedPiece != NULL)
		{
			if (targetedPiece->isSameType(piece)) return false;
		}

		return true;
	}
};