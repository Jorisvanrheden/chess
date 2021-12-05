#pragma once

#include "Board.h"
#include "Parser.h"

#include "PlayerSelector.h"
#include "BoardAnalyzer.h"

#include "ChessFactoryDefault.h"

class CHESS_API
{
public:
	CHESS_API() {}
	~CHESS_API() {}

	void initialize() 
	{
		IChessFactory* factory = new ChessFactoryDefault();
		IBoardAnalyzer* analyzer			  = factory->createBoardAnalyzer();
		IFilter<Piece>* filter				  = factory->createPieceFilter();
		MoveValidationManager* moveValidation = factory->createMoveValidationManager();
		IBoardPopulator* populator			  = factory->createBoardPopulator();

		board = new	Board(moveValidation, filter, analyzer, populator);
		playerSelector = new PlayerSelector();

		board->populate();
	}

	void load(const std::string& filepath) 
	{
		Parser parser(*board, *playerSelector);
		MoveContext context = parser.parse(filepath);
	}

	std::vector<Coordinate> getValidatedMoves(const Coordinate& coordinate) 
	{
		return board->getValidatedMoves(coordinate);
	}

	std::vector<Coordinate> getRawMoves(const Coordinate& coordinate)
	{
		return board->getRawMoves(coordinate);
	}

	void movePiece(const Coordinate& origin, const Coordinate& target) 
	{
		//check if the piece at origin is the type that should move now
		if (!playerSelector->canMove(*board, origin)) 
		{
			std::cout << "It is not the turn of the owner of the selected piece" << std::endl;
			return;
		}

        if (!board->isValidMove(origin, target)) 
        {
            std::cout << "The attempted move is not valid" << std::endl;
            return;
        }

        //Retrieve the relevant move set associated with the origin and target
        MoveSet* moveSet = board->getMoveSet(origin, target);

		//Validate the move set
		if (moveSet)
		{			
			bool moveSetResult = board->applyMoveSet(moveSet);
			if (moveSetResult) 
			{
				board->analyzeStatus(playerSelector->getActivePlayer());
				playerSelector->nextPlayer();
				board->analyzeStatus(playerSelector->getActivePlayer());
			}
		}
		else 
		{
			std::cout << "This move is not valid given the origin location" << std::endl;
		}
	}

	int getPlayerCount() 
	{
		return playerSelector->getPlayerCount();
	}

    void print() 
    {
        board->print();
    }

	std::vector<std::vector<int>> getBoardStatus(int playerID)
	{
		return board->getBoardStatus(playerID);
	}

private:
	Board* board;

	IBoardPopulator* populator;
	IPlayerSelector* playerSelector;
};

