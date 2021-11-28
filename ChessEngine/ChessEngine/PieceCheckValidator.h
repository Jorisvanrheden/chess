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
        //Create the moveset from the origin and target
        std::vector<std::tuple<Coordinate, Coordinate>> moves;
        moves.push_back(std::tuple<Coordinate, Coordinate>{origin, target});

        MoveSet move(moves);

        //apply the the moveset to the board
        board.applyMoveSet(&move);

		//if the piece is checked, the move is not valid
		bool result = !checkDetector->isChecked(board, piece->getPlayerType());

		//undo the moveset
        board.undoLatestMoveSet();

		return result;
	}
	
private:
	IPieceCheckDetector* checkDetector;
};