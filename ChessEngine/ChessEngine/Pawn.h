#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const PlayerType& type) : Piece(type) {}
	~Pawn() {}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A pawn can only move up or down (depending on it's type)
		std::vector<Coordinate> moves;

		switch (type) 
		{
		case PlayerType::BLACK:
			moves.push_back(Coordinate(coordinate.getX(), coordinate.getY() + 1));
			break;
		case PlayerType::WHITE:
			moves.push_back(Coordinate(coordinate.getX(), coordinate.getY() - 1));
			break;
		default:
			break;
		}

		return moves;
	}
};