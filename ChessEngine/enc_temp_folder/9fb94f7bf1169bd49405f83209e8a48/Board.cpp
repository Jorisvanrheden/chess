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

    //Set the targets back to the pieces that were located there
    for (const auto& target : content.targets)
    {
        setPieceAt(target->getCurrentCoordinate(), target);
    }

    //Set the target to NULL
    setPieceAt(content.to, NULL);

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

    //- retrieve a list of possible move sets

    //So what we want is:
    //- One MoveSet per piece, given the origin and the target

    //First get all movesets from a piece
    //Then filter out the one needed given the target
    //But this doesnt fully allow data transfer
    //Instead maybe create a separate getter in PIECE, like:
    MoveSet* moveSet = piece->getMoveSet(target, *this);
    return moveSet;

    ////but we dont need all moves, only moves that have the same starting coordinate
    //std::vector<Coordinate> moves = getAllPieceMoves(origin);
    //std::vector<MoveSet*> sets = piece->transformMoves(moves, *this);

    ////- compare the start and end position of the initial piece
    //for (auto& set : sets)
    //{
    //    //Only look for index 0, as castling is the only case where more contents are available
    //    //For castling, king should be the initiating move
    //    MoveContent content = set->getContent(0);

    //    if (content.from == origin && content.to == target)
    //    {
    //        return set;
    //    }
    //}

    ////Return null if the given origin and target coordinates are not a valid combination
    //return NULL;
}