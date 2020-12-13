#pragma once

#include "IMoveSet.h"
#include <tuple>

class MoveSetMultiple : public IMoveSet 
{
public:
	MoveSetMultiple(std::vector<std::tuple<Coordinate, Coordinate>>& moves): moves(moves) 
	{

	}

	bool move(Board& board)
	{
		for (int i = 0; i < moves.size(); i++) 
		{
			bool result = board.movePiece(std::get<0>(moves[i]), std::get<1>(moves[i]));
			if (!result) return false;
		}

		return true;
	}

private:
	std::vector<std::tuple<Coordinate, Coordinate>> moves;
};