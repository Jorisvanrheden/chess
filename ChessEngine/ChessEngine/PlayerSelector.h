#pragma once

#include "IPlayerSelector.h"
#include "GameConstants.h"
#include "Board.h"

class PlayerSelector : public IPlayerSelector
{
public:
	PlayerSelector(Board& board) : board(board)
	{
		//start with white
		playerIndex = 0;
	}
	~PlayerSelector() {}

	void moveSet(IMoveSet* set) 
	{
		//move the piece on the board
		bool movedSuccesfully = set->move(board);
		if (movedSuccesfully)
		{
			for (int i = 0; i < players.size(); i++)
			{
				if (i == playerIndex) continue;

				int playerStatus = board.analyzeStatus(players[i]);
				std::cout << "Player " << i << " -> " << playerStatus << std::endl;
			}

			//iterate active player index
			playerIndex = (playerIndex + 1) % players.size();
		}
	}

	std::vector<Coordinate> getAvailableMoves(const Coordinate& coordinate) 
	{
		if (!canMove(coordinate)) return std::vector<Coordinate>();

		return board.getAvailableMoves(coordinate);
	}

	PLAYER_TYPE getActivePlayer() 
	{
		return players[playerIndex];
	}

private:
	Board& board;

	int playerIndex = 0;
	std::vector<PLAYER_TYPE> players{ PLAYER_TYPE::WHITE, PLAYER_TYPE::BLACK };

	bool canMove(const Coordinate& coordinate)
	{
		Piece* piece = board.getPieceAt(coordinate);
		if (piece != NULL)
		{
			return piece->isSameType(players[playerIndex]);
		}

		return false;
	}
};