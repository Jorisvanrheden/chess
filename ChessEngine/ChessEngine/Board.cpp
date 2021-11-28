#include "Board.h"

Board::Board(MoveValidationManager* validationManager, IMoveHandler* moveHandler, IFilter<Piece>* pieceFilter, IBoardAnalyzer* boardAnalyzer, IBoardPopulator* boardPopulator)
    : validationManager(validationManager),
    moveHandler(moveHandler),
    pieceFilter(pieceFilter),
    boardAnalyzer(boardAnalyzer),
    boardPopulator(boardPopulator)
{
    //init empty board
    matrix = std::vector<std::vector<Piece*>>(boardPopulator->getWidth());
    for (int i = 0; i < boardPopulator->getWidth(); i++)
    {
        std::vector<Piece*> row(boardPopulator->getHeight());

        matrix[i] = row;
    }
}
Board::~Board() {}

bool Board::applyMoveSet(MoveSet* moveSet)
{
    for (int i = 0; i < moveSet->getMoveCount(); i++)
    {
        bool result = movePiece(moveSet->getStart(i), moveSet->getTarget(i));

        if (!result) return false;
    }

    history.push_back(moveSet);

    return true;
}

void Board::undoLatestMoveSet() 
{
    history.pop_back();
}