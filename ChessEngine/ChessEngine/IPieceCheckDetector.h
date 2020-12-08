#pragma once

#include "Board.h"
#include "SamePlayerTypeSpecification.h"
#include "OtherPlayerTypeSpecification.h"
#include "PieceTypeSpecification.h"
#include "AndSpecification.h"

class IPieceCheckDetector
{
public:
	virtual bool isChecked(Board& board, PLAYER_TYPE player) = 0;
};