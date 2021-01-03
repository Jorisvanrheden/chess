#pragma once

#include "IBoardPopulator.h"
#include "PieceCollection.h"

class DefaultBoardPopulator : public IBoardPopulator
{
public:
	DefaultBoardPopulator()
	{

	}
	~DefaultBoardPopulator() {}

private:

	const int SIZE_X = 8;
	const int SIZE_Y = 8;

	int getWidth() 
	{
		return SIZE_X;
	}
	int getHeight()
	{
		return SIZE_Y;
	}

	void populate(Board& board)
	{
		std::vector<std::vector<int>> board_representation
		{
			{4,2,3,5,6,3,2,4},
			{1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{7,7,7,7,7,7,7,7},
			{10,8,9,11,12,9,8,10}
		};

		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				Coordinate coord(i, j);
				PLAYER_TYPE type = (board_representation[i][j] > PIECE_COUNT) ? PLAYER_TYPE::WHITE : PLAYER_TYPE::BLACK;
				Piece* piece = createPiece(board_representation[i][j], type);

				if (piece)
				{
					board.setPieceAt(Coordinate(j, i), piece);
				}
			}
		}

		King* king_black = (King*)board.getPieceAt(Coordinate(4, 0));
		King* king_white = (King*)board.getPieceAt(Coordinate(4, 7));

		king_black->combination = new CastleCombination(king_black, board.getPieceAt(Coordinate(7, 0)), board.getPieceAt(Coordinate(0, 0)));
		king_white->combination = new CastleCombination(king_white, board.getPieceAt(Coordinate(7, 7)), board.getPieceAt(Coordinate(0, 7)));
	}

	Piece* createPiece(int index, PLAYER_TYPE type)
	{
		if (index > PIECE_COUNT)index -= PIECE_COUNT;

		switch (index)
		{
		case PIECE_TYPE::PAWN: 
		{
			Direction direction(0, 1);

			if (type == PLAYER_TYPE::BLACK)
			{
				direction = Direction(0, 1);
			}
			else if (type == PLAYER_TYPE::WHITE)
			{
				direction = Direction(0, -1);
			}
			return new Pawn(type, direction);
		}		
		case PIECE_TYPE::KNIGHT:
			return new Knight(type);
		case PIECE_TYPE::BISHOP:
			return new Bishop(type);
		case PIECE_TYPE::ROOK:
			return new Rook(type);
		case PIECE_TYPE::QUEEN:
			return new Queen(type);
		case PIECE_TYPE::KING:
			return new King(type);

		default:
			return NULL;
		}
	}

	const int PIECE_COUNT = 6;
};