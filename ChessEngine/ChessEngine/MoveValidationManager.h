#pragma once

#include "IMoveValidator.h"
#include "Piece.h"
#include "Coordinate.h"
#include "Board.h"
#include <vector>

class MoveValidationManager
{
public:
	bool isMoveValid(const Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
		for (auto& validator : validators) 
		{
			if (!validator->isMoveValid(board, piece, origin, target)) return false;
		}

		return true;
	}

	void addValidator(IMoveValidator* validator) 
	{
		validators.push_back(validator);
	}

private:
	std::vector<IMoveValidator*> validators;
};