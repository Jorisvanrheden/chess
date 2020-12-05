#pragma once

#include "IMoveValidator.h"
#include "Piece.h"
#include "Coordinate.h"
#include <vector>

class MoveValidationManager
{
public:
	bool isMoveValid(Piece* piece, const Coordinate& coordinate) 
	{
		for (auto& validator : validators) 
		{
			if (!validator->isMoveValid(piece, coordinate)) return false;
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