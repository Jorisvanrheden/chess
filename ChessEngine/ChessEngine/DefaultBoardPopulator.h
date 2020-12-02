#pragma once

#include "IBoardPopulator.h"
#include "PieceCollection.h"

class DefaultBoardPopulator : public IBoardPopulator 
{
public:
	DefaultBoardPopulator(Board& board) 
	{
		populate(board);
	}
	~DefaultBoardPopulator() {}

private:
	void populate(Board& board)
	{
		populatePiecesDefault(board, Coordinate(0, 0), new Rook(PLAYER_TYPE::BLACK), new Rook(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(1, 0), new Knight(PLAYER_TYPE::BLACK), new Knight(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(2, 0), new Bishop(PLAYER_TYPE::BLACK), new Bishop(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(5, 0), new Bishop(PLAYER_TYPE::BLACK), new Bishop(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(6, 0), new Knight(PLAYER_TYPE::BLACK), new Knight(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(7, 0), new Rook(PLAYER_TYPE::BLACK), new Rook(PLAYER_TYPE::WHITE));

		populatePiecesDefault(board, Coordinate(3, 0), new Queen(PLAYER_TYPE::BLACK), new Queen(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(4, 0), new King(PLAYER_TYPE::BLACK), new King(PLAYER_TYPE::WHITE));

		populatePiecesDefault(board, Coordinate(2, 2), new Queen(PLAYER_TYPE::WHITE), new Queen(PLAYER_TYPE::BLACK));
		populatePiecesDefault(board, Coordinate(4, 2), new Queen(PLAYER_TYPE::WHITE), new Queen(PLAYER_TYPE::BLACK));

		//Add pawns
		for (int i = 0; i < board.getSizeX(); i++)
		{
			populatePiecesDefault(board, Coordinate(i, 1), new Pawn(PLAYER_TYPE::BLACK), new Pawn(PLAYER_TYPE::WHITE));
		}
	}

	void populatePiecesDefault(Board& board, Coordinate coordinate, Piece* black, Piece* white)
	{
		board.setPieceAt(coordinate, black);

		//mirrored
		board.setPieceAt(Coordinate(coordinate.getX(), board.getSizeY() - coordinate.getY() - 1), white);
	}
};