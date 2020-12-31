#pragma once

#include "Board.h"
#include "Parser.h"

//TODO: refactor these dependencies by using an abstract factory
// then make an implementation for a default game first
#include "DefaultBoardPopulator.h"
#include "TestingBoardPopulator.h"

#include "PlayerSelector.h"

#include "DefaultMoveHandler.h"

#include "FriendyFireValidatorh.h"
#include "EnPassantValidator.h"
#include "PieceCheckValidator.h"

#include "PieceFilter.h"

#include "BoardAnalyzer.h"
#include "PieceCheckDetector.h"

class CHESS_API
{
public:
	CHESS_API() {}
	~CHESS_API() {}

	void initialize() 
	{
		IPieceCheckDetector* checkDetector = new PieceCheckDetector(PIECE_TYPE::KING);

		MoveValidationManager* validationManager = new MoveValidationManager();
		validationManager->addValidator(new FriendlyFireValidator());
		validationManager->addValidator(new EnPassantValidator());
		validationManager->addValidator(new PieceCheckValidator(checkDetector));

		IMoveHandler* moveHandler = new DefaultMoveHandler();

		IFilter<Piece>* pieceFilter = new PieceFilter();

		IBoardAnalyzer* boardAnalyzer = new BoardAnalyzer(checkDetector);

		board = new	Board(validationManager, moveHandler, pieceFilter, boardAnalyzer);
		populator = new DefaultBoardPopulator(*board);
		playerSelector = new PlayerSelector(*board);
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
		if (!playerSelector->canMove(origin)) 
		{
			std::cout << "It is not the turn of the owner of the selected piece" << std::endl;
			return;
		}

		//validate if the target is indeed a valid move
		bool containsMove = board->verifyMove(origin, target);		
		if (containsMove) 
		{
			IMoveSet* moveSet = board->getMoveSet(origin, target);
			playerSelector->moveSet(moveSet);
		}
		else 
		{
			std::cout << "This move is not valid given the origin location" << std::endl;
		}
	}

	void getBoardStatus() 
	{
		board->print();
	}

private:
	Board* board;

	IBoardPopulator* populator;
	IPlayerSelector* playerSelector;
};

