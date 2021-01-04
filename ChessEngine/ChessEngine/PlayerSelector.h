#pragma once

#include "IPlayerSelector.h"
#include "GameConstants.h"
#include "Board.h"

class PlayerSelector : public IPlayerSelector
{
public:
	PlayerSelector()
	{
		//start with white
		playerIndex = 0;
	}
	~PlayerSelector() {}

	void nextPlayer() 
	{
		//iterate active player index
		playerIndex = (playerIndex + 1) % players.size();
	}

	PLAYER_TYPE getActivePlayer() 
	{
		return players[playerIndex];
	}

	bool canMove(const Board& board, const Coordinate& coordinate)
	{
		Piece* piece = board.getPieceAt(coordinate);
		if (piece != NULL)
		{
			return piece->isSameType(players[playerIndex]);
		}

		return false;
	}

	int getPlayerCount() 
	{
		return players.size();
	}

private:
	int playerIndex = 0;
	std::vector<PLAYER_TYPE> players{ PLAYER_TYPE::WHITE, PLAYER_TYPE::BLACK };
};