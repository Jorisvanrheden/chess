#pragma once

#include "IMoveValidator.h"
#include "IPieceCheckDetector.h"

class PieceCheckValidator : public IMoveValidator
{
public:
	PieceCheckValidator(IPieceCheckDetector* checkDetector) : checkDetector(checkDetector)
	{
		
	}
	~PieceCheckValidator() {}

	bool isMoveValid(Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
        //TODO: don't pass origin and target, but pass a MoveSet instead
        //That covers all data, so you don't have to keep constructing these objects 
        //over and over again

        MoveSet* moveSet = board.getMoveSet(origin, target);

        //apply the the moveset to the board
        board.applyMoveSet(moveSet);

		//if the piece is checked, the move is not valid
		bool result = !checkDetector->isChecked(board, piece->getPlayerType());

		//undo the moveset
        board.undoLatestMoveSet();

		return result;
	}
	
private:
	IPieceCheckDetector* checkDetector;
};