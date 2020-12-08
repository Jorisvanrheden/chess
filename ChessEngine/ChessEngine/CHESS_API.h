#pragma once

#include "Board.h"

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
		IPieceCheckDetector* checkDetector = new PieceCheckDetector(PIECE_TPYE::KING);

		MoveValidationManager* validationManager = new MoveValidationManager();
		validationManager->addValidator(new FriendlyFireValidator());
		validationManager->addValidator(new EnPassantValidator());
		validationManager->addValidator(new PieceCheckValidator(checkDetector));

		IMoveHandler* moveHandler = new DefaultMoveHandler();

		IFilter<Piece>* pieceFilter = new PieceFilter();

		IBoardAnalyzer* boardAnalyzer = new BoardAnalyzer(checkDetector);

		board = new	Board(validationManager, moveHandler, pieceFilter, boardAnalyzer);
		populator = new TestingBoardPopulator(*board);
		playerSelector = new PlayerSelector(*board);

		board->print();
	}

	std::vector<Coordinate> getMoves(const Coordinate& coordinate) 
	{
		return playerSelector->getAvailableMoves(coordinate);
	}

	void movePiece(const Coordinate& origin, const Coordinate& target) 
	{
		playerSelector->movePiece(origin, target);
	}

private:
	Board* board;

	IBoardPopulator* populator;
	IPlayerSelector* playerSelector;
};

