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
		populatePiecesDefault(board, Coordinate(0, 0), new Rook(PlayerType::BLACK), new Rook(PlayerType::WHITE));
		populatePiecesDefault(board, Coordinate(1, 0), new Knight(PlayerType::BLACK), new Knight(PlayerType::WHITE));
		populatePiecesDefault(board, Coordinate(2, 0), new Bishop(PlayerType::BLACK), new Bishop(PlayerType::WHITE));
		populatePiecesDefault(board, Coordinate(5, 0), new Bishop(PlayerType::BLACK), new Bishop(PlayerType::WHITE));
		populatePiecesDefault(board, Coordinate(6, 0), new Knight(PlayerType::BLACK), new Knight(PlayerType::WHITE));
		populatePiecesDefault(board, Coordinate(7, 0), new Rook(PlayerType::BLACK), new Rook(PlayerType::WHITE));

		board.setPieceAt(Coordinate(3, 0), new Queen(PlayerType::WHITE));
		board.setPieceAt(Coordinate(4, 0), new King(PlayerType::WHITE));

		board.setPieceAt(Coordinate(3, 7), new Queen(PlayerType::BLACK));
		board.setPieceAt(Coordinate(4, 7), new King(PlayerType::BLACK));

		//Add pawns
		for (int i = 0; i < board.getSizeX(); i++) 
		{
			populatePiecesDefault(board, Coordinate(i, 1), new Pawn(PlayerType::BLACK), new Pawn(PlayerType::WHITE));
		}
	}

private:
	void populatePiecesDefault(Board& board, Coordinate coordinate, Piece* black, Piece* white)
	{
		board.setPieceAt(coordinate, black);

		//rotated
		board.setPieceAt(Coordinate(board.getSizeX() - coordinate.getX() - 1, board.getSizeY() - coordinate.getY() - 1), white);
	}
};