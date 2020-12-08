#pragma once

#include "ISpecification.h"
#include "Piece.h"

class PieceTypeSpecification : public ISpecification<Piece>
{
public:
	PieceTypeSpecification(PIECE_TYPE type) : type(type) {}
	~PieceTypeSpecification() {}

	bool isSatisfiedBy(Piece* piece)
	{
		return piece->getID() == type;
	}

private:
	PIECE_TYPE type;
};