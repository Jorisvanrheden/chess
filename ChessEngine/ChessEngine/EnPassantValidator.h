#pragma once

#include "IMoveValidator.h"

class EnPassantValidator : public IMoveValidator
{
	bool isMoveValid(const Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
		return true;
	}
};