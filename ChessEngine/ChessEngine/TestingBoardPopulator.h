#pragma once

#include "IBoardPopulator.h"
#include "PieceCollection.h"

class TestingBoardPopulator : public IBoardPopulator
{
public:
	TestingBoardPopulator(Board& board)
	{
		populate(board);
	}
	~TestingBoardPopulator() {}

private:
	void populate(Board& board)
	{
		board.setPieceAt(Coordinate(0, 0), new King(PLAYER_TYPE::BLACK));
		board.setPieceAt(Coordinate(1, 0), new Knight(PLAYER_TYPE::BLACK));
		board.setPieceAt(Coordinate(0, 1), new Knight(PLAYER_TYPE::BLACK));
		board.setPieceAt(Coordinate(1, 1), new Knight(PLAYER_TYPE::BLACK));

		board.setPieceAt(Coordinate(0, 4), new Knight(PLAYER_TYPE::WHITE));
		board.setPieceAt(Coordinate(0,7), new Knight(PLAYER_TYPE::WHITE));
	}
};