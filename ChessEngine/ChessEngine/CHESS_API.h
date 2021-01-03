#pragma once

#include "Board.h"
#include "Parser.h"

#include "DefaultBoardPopulator.h"
#include "TestingBoardPopulator.h"

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
		IMoveHandler* moveHandler			  = factory->createMoveHandler();
		IFilter<Piece>* filter				  = factory->createPieceFilter();
		MoveValidationManager* moveValidation = factory->createMoveValidationManager();

		board = new	Board(moveValidation, moveHandler, filter, analyzer);
		populator = new DefaultBoardPopulator(*board);
		playerSelector = new PlayerSelector();
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

		//validate if the target is indeed a valid move
		bool containsMove = board->verifyMove(origin, target);		
		if (containsMove) 
		{
			IMoveSet* moveSet = board->getMoveSet(origin, target);
			
			bool moveSetResult = board->applyMoveSet(moveSet);
			if (moveSetResult) 
			{
				board->analyzeStatus(playerSelector->getActivePlayer());
				playerSelector->nextPlayer();
			}
		}
		else 
		{
			std::cout << "This move is not valid given the origin location" << std::endl;
		}
	}

	std::vector<std::vector<int>> getBoardStatus()
	{
		board->print();
		return board->getBoardStatus();
	}

private:
	Board* board;

	IBoardPopulator* populator;
	IPlayerSelector* playerSelector;
};

