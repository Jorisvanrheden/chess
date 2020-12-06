#pragma once

#include "ISpecification.h"
#include "Piece.h"

class OtherPlayerTypeSpecification : public ISpecification<Piece>
{
public:
	OtherPlayerTypeSpecification(PLAYER_TYPE type) : type(type) {}
	~OtherPlayerTypeSpecification() {}

	bool isSatisfiedBy(Piece* piece) 
	{
		return !piece->isSameType(type);
	}

private:
	PLAYER_TYPE type;
};