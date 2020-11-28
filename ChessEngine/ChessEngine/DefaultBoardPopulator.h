#pragma once

#include "IBoardPopulator.h"
#include "PieceCollection.h"

class DefaultBoardPopulator : public IBoardPopulator 
{
public:
	DefaultBoardPopulator() {}
	~DefaultBoardPopulator() {}

	void populate(Board& board) 
	{
		board.setPieceAt(Coordinate(0, 1), new Knight(PlayerType::BLACK));
		board.setPieceAt(Coordinate(0, 7), new Knight(PlayerType::BLACK));

		board.setPieceAt(Coordinate(7, 1), new Knight(PlayerType::WHITE));
		board.setPieceAt(Coordinate(7, 7), new Knight(PlayerType::WHITE));
	}
};