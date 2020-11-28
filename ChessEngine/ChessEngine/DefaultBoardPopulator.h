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
		board.setPieceAt(Coordinate(1, 0), new Knight(PlayerType::BLACK));
		board.setPieceAt(Coordinate(7, 0), new Knight(PlayerType::BLACK));

		board.setPieceAt(Coordinate(4, 4), new Bishop(PlayerType::BLACK));
		board.setPieceAt(Coordinate(5, 5), new King(PlayerType::BLACK));

		//Add pawns (black side)
		for (int i = 0; i < board.getSizeX(); i++) 
		{
			board.setPieceAt(Coordinate(i, 1), new Pawn(PlayerType::BLACK));
		}
	}
};