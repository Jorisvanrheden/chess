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

	bool isMoveValid(const Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
		//copy the board state
		Board copy = Board(board);

		//apply the the move to the piece onto the copied board
		copy.movePiece(origin, target);

		//if the piece is checked, the move is not valid
		bool result = !checkDetector->isChecked(copy, piece->getPlayerType());

		//remove the history from the piece since it's played on a copied board
		piece->removeLastCoordinate();

		return result;
	}
	
private:
	IPieceCheckDetector* checkDetector;
};