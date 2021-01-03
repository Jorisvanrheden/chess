#pragma once

#include "IChessFactory.h"

#include "BoardAnalyzer.h"
#include "DefaultBoardPopulator.h"
#include "PieceCheckDetector.h"

#include "FriendyFireValidatorh.h"
#include "EnPassantValidator.h"
#include "PieceCheckValidator.h"

#include "DefaultMoveHandler.h"
#include "PieceFilter.h"

class ChessFactoryDefault : public IChessFactory
{
public:

	ChessFactoryDefault() 
	{
		checkDetector = new PieceCheckDetector(PIECE_TYPE::KING);
	}
	~ChessFactoryDefault()
	{
		delete checkDetector;
	}

	IBoardAnalyzer* createBoardAnalyzer() 
	{
		return new BoardAnalyzer(checkDetector);
	}

	IBoardPopulator* createBoardPopulator() 
	{
		return new DefaultBoardPopulator();
	}

	IMoveHandler* createMoveHandler() 
	{
		return new DefaultMoveHandler();
	}

	IFilter<Piece>* createPieceFilter() 
	{
		return new PieceFilter();
	}

	MoveValidationManager* createMoveValidationManager() 
	{
		MoveValidationManager* validationManager = new MoveValidationManager();
		validationManager->addValidator(new FriendlyFireValidator());
		validationManager->addValidator(new EnPassantValidator());
		validationManager->addValidator(new PieceCheckValidator(checkDetector));

		return validationManager;
	}

private:
	IPieceCheckDetector* checkDetector;
};