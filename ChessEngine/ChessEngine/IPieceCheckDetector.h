#pragma once

#include "Board.h"

class IPieceCheckDetector
{
public:
	virtual bool isChecked(const Board& board, PLAYER_TYPE player) = 0;
};