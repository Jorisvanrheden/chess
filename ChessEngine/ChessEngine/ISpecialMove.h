#pragma once

#include "IMoveSet.h"

class ISpecialMove 
{
public:
	virtual IMoveSet* getMove(const std::string& moveString, PLAYER_TYPE type) = 0;
};