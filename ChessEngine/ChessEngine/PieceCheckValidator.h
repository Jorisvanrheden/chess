#pragma once

#include "IMoveValidator.h"
#include "IPieceCheckDetector.h"

#include "PieceTypeSpecification.h"
#include "OtherPlayerTypeSpecification.h"	
#include "SamePlayerTypeSpecification.h"	
#include "AndSpecification.h"

class PieceCheckValidator : public IMoveValidator
{
public:
	PieceCheckValidator(IPieceCheckDetector* checkDetector) : checkDetector(checkDetector)
	{
		
	}
	~PieceCheckValidator() {}

	bool isMoveValid(const Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
		//copy the board state
		Board copy = Board(board);

		//apply the the move to the piece onto the copied board
		copy.movePiece(origin, target);

		//if the piece is checked, the move is not valid
		return !checkDetector->isChecked(copy, piece->getPlayerType());
	}
	
private:
	IPieceCheckDetector* checkDetector;
};