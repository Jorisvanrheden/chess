#pragma once

#include "IBoardAnalyzer.h"
#include "IPieceCheckDetector.h"

class BoardAnalyzer : public IBoardAnalyzer
{
public:
	BoardAnalyzer(IPieceCheckDetector* checkDetector) : checkDetector(checkDetector)
	{

	}
	~BoardAnalyzer() {}

	// 0 = not game over
	// 1 = checked
	// 2 = game over (checkmate)
	// 3 = game over (stalemate)
	int analyzeStatus(Board& board, PLAYER_TYPE player)
	{
		//look at the available(logic validated) moves for each piece of that player
		bool canMove = hasAvailableMoves(board, player);

		bool isPlayerChecked = checkDetector->isChecked(board, player);

		if (!canMove) 
		{
			//if a player has no available moves, but the player is checked, it's checkmate
			if (isPlayerChecked) return 2;

			//if a player has no available moves, but is also not checked, it's stalemate
			else return 3;
		}

		//if the player is checked return
		if (isPlayerChecked) return 1;
		
		return 0;
	}

private:
	IPieceCheckDetector* checkDetector;

	bool hasAvailableMoves(Board& board, PLAYER_TYPE player) 
	{
		SamePlayerTypeSpecification sameTypeSpec(player);
		auto pieces = board.filter(sameTypeSpec);

		//loop through all pieces and check if it contains any logic validated moves 
		for (auto& piece : pieces) 
		{
			auto availableMoves = board.getValidatedMoves(piece->getCurrentCoordinate());
			if (availableMoves.size() > 0) return true;
		}
		return false;
	}
};