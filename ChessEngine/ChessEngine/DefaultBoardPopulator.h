#pragma once

#include "IBoardPopulator.h"
#include "PieceCollection.h"
#include "CastleCombination.h"

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
		Rook* rook_short_white = new Rook(PLAYER_TYPE::WHITE);
		Rook* rook_short_black = new Rook(PLAYER_TYPE::BLACK);

		Rook* rook_long_white = new Rook(PLAYER_TYPE::WHITE);
		Rook* rook_long_black = new Rook(PLAYER_TYPE::BLACK);

		King* king_white = new King(PLAYER_TYPE::WHITE);
		King* king_black = new King(PLAYER_TYPE::BLACK);

		populatePiecesDefault(board, Coordinate(0, 0), rook_long_black, rook_long_white);
		populatePiecesDefault(board, Coordinate(1, 0), new Knight(PLAYER_TYPE::BLACK), new Knight(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(2, 0), new Bishop(PLAYER_TYPE::BLACK), new Bishop(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(5, 0), new Bishop(PLAYER_TYPE::BLACK), new Bishop(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(6, 0), new Knight(PLAYER_TYPE::BLACK), new Knight(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(7, 0), rook_short_black, rook_short_white);

		populatePiecesDefault(board, Coordinate(3, 0), new Queen(PLAYER_TYPE::BLACK), new Queen(PLAYER_TYPE::WHITE));
		populatePiecesDefault(board, Coordinate(4, 0), king_black, king_white);

		//Add pawns
		for (int i = 0; i < board.getSizeX(); i++)
		{
			populatePiecesDefault(board, Coordinate(i, 1), new Pawn(PLAYER_TYPE::BLACK), new Pawn(PLAYER_TYPE::WHITE));
		}


		//Adding special moves to the board
		board.addSpecialMove(new CastleCombination(king_black, rook_short_black, rook_long_black));
		board.addSpecialMove(new CastleCombination(king_white, rook_short_white, rook_long_white));
	}

	void populatePiecesDefault(Board& board, Coordinate coordinate, Piece* black, Piece* white)
	{
		board.setPieceAt(coordinate, black);

		//mirrored
		board.setPieceAt(Coordinate(coordinate.getX(), board.getSizeY() - coordinate.getY() - 1), white);
	}
};