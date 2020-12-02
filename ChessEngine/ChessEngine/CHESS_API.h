#pragma once

#include "Board.h"

//TODO: refactor these dependencies by using an abstract factory
// then make an implementation for a default game first
#include "DefaultBoardPopulator.h"
#include "PlayerSelector.h"

class CHESS_API
{
public:
	CHESS_API() {}
	~CHESS_API() {}

	void initialize() 
	{
		populator = new DefaultBoardPopulator(board);
		playerSelector = new PlayerSelector(board);
	}

	std::vector<Coordinate> getMoves(const Coordinate& coordinate) 
	{
		return playerSelector->getAvailableMoves(coordinate);
	}

	void movePiece(const Coordinate& origin, const Coordinate& target) 
	{
		return playerSelector->movePiece(origin, target);
	}

private:
	Board board;

	IBoardPopulator* populator;
	IPlayerSelector* playerSelector;
};

