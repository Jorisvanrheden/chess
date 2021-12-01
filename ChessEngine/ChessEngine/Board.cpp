#include "Board.h"

Board::Board(MoveValidationManager* validationManager, IFilter<Piece>* pieceFilter, IBoardAnalyzer* boardAnalyzer, IBoardPopulator* boardPopulator)
    : validationManager(validationManager),
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

void Board::applyMoveContent(const MoveContent& content)
{
    //set the origin to NULL
    setPieceAt(content.from, NULL);

    //set all targets to NULL
    for (const auto& target : content.targets)
    {
        setPieceAt(target->getCurrentCoordinate(), NULL);
    }

    //set the active piece end location
    setPieceAt(content.to, content.activePiece);

    //Update the piece's coordinate history
    content.activePiece->addCoordinateToHistory(content.to);
}

void Board::undoMoveContent(const MoveContent& content)
{
    //To undo, the active piece must be set back to the from position
    setPieceAt(content.from, content.activePiece);

    //Set the target to NULL - it is important this happens before the targets are reset
    //In case no target, the square is still set properly, but otherwise targets are overwritten again
    setPieceAt(content.to, NULL);

    //Set the targets back to the pieces that were located there
    for (const auto& target : content.targets)
    {
        setPieceAt(target->getCurrentCoordinate(), target);
    }

    //Undo the piece history update
    content.activePiece->removeLastCoordinate();
}

bool Board::applyMoveSet(MoveSet* moveSet)
{
    for (int i = 0; i < moveSet->getMoveCount(); i++)
    {
        applyMoveContent(moveSet->getContent(i));
    }

    history.push_back(moveSet);

    return true;
}

void Board::undoLatestMoveSet() 
{
    if (history.size() == 0) return;

    MoveSet* moveSet = history[history.size() - 1];

    for (int i = 0; i < moveSet->getMoveCount(); i++)
    {
        undoMoveContent(moveSet->getContent(i));
    }

    //remove the history entry
    history.pop_back();
}

//Given a certain start and end position of a selected piece,
//The available moveset should be generated
MoveSet* Board::getMoveSet(const Coordinate& origin, const Coordinate& target)
{
    Piece* piece = getPieceAt(origin);
    if (piece) 
    {
        return piece->getMoveSet(target, *this);
    }

    return NULL;
}