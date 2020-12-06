#pragma once

#include "IFilter.h"
#include "Piece.h"

class PieceFilter : public IFilter<Piece>
{
public:
	std::vector<Piece*> filter(std::vector<Piece*> items, ISpecification<Piece>& specification) 
	{
		std::vector<Piece*> pieces;
		for (auto& item : items) 
		{
			if (item->getID() == PIECE_TPYE::KING) 
			{
				std::cout << "hti" << std::endl;
			}

			if (specification.isSatisfiedBy(item))
			{
				pieces.push_back(item);
			}
		}
		return pieces;
	}
};