#pragma once

#include "IPlayerSelector.h"
#include "GameConstants.h"
#include "Board.h"

class PlayerSelector : public IPlayerSelector
{
public:
	PlayerSelector(const Board& board) : board(board)
	{
		//start with white
		playerIndex = 0;
	}
	~PlayerSelector() {}

	void movePiece(const Coordinate& origin, const Coordinate& target)
	{
		if (!canMove(origin)) return;

		//move the piece on the board
		bool movedSuccesfully = board.movePiece(origin, target);
		if (movedSuccesfully) 
		{
			//iterate active player index
			playerIndex = (playerIndex + 1) % players.size();
		}
	}

	std::vector<Coordinate> getAvailableMoves(const Coordinate& coordinate) 
	{
		if (!canMove(coordinate)) return std::vector<Coordinate>();

		return board.getAvailableMoves(coordinate);
	}

private:
	Board board;

	int playerIndex = 0;
	std::vector<PLAYER_TYPE> players{ PLAYER_TYPE::WHITE, PLAYER_TYPE::BLACK };

	bool canMove(const Coordinate& coordinate)
	{
		Piece* piece = board.getPieceAt(coordinate);
		if (piece != NULL)
		{
			return !piece->isSameType(players[playerIndex]);
		}

		return false;
	}
};