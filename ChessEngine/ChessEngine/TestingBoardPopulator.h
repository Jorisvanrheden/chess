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
		populatePiecesDefault(board, Coordinate(4, 0), new King(PLAYER_TYPE::BLACK), new King(PLAYER_TYPE::WHITE));

		board.setPieceAt(Coordinate(4, 1), new Rook(PLAYER_TYPE::BLACK));

		board.setPieceAt(Coordinate(4, 5), new Rook(PLAYER_TYPE::WHITE));
	}

	void populatePiecesDefault(Board& board, Coordinate coordinate, Piece* black, Piece* white)
	{
		board.setPieceAt(coordinate, black);

		//mirrored
		board.setPieceAt(Coordinate(coordinate.getX(), board.getSizeY() - coordinate.getY() - 1), white);
	}
};