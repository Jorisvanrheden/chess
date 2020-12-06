#pragma once

#include "ISpecification.h"
#include "Piece.h"

class SamePlayerTypeSpecification : public ISpecification<Piece>
{
public:
	SamePlayerTypeSpecification(PLAYER_TYPE type) : type(type) {}
	~SamePlayerTypeSpecification() {}

	bool isSatisfiedBy(Piece* piece)
	{
		return piece->isSameType(type);
	}

private:
	PLAYER_TYPE type;
};