#pragma once

#include "IBoardAnalyzer.h"
#include "IMoveHandler.h"
#include "IFilter.h"
#include "IBoardPopulator.h"

//should be abstract....
#include "MoveValidationManager.h"

class IChessFactory 
{
public:
	virtual IBoardAnalyzer* createBoardAnalyzer() = 0;
	virtual IBoardPopulator* createBoardPopulator() = 0;
	virtual IMoveHandler* createMoveHandler() = 0;
	virtual IFilter<Piece>* createPieceFilter() = 0;
	virtual MoveValidationManager* createMoveValidationManager() = 0;
};