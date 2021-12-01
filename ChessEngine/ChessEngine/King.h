#pragma once
#include "Piece.h"

#include "CastleCombination.h"

class King : public Piece
{
public:
	King(const PLAYER_TYPE& type) : Piece(type) {}
	~King() {}

	PIECE_TYPE getID()
	{
		return PIECE_TYPE::KING;
	}

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		std::vector<Coordinate> moves;

		//horizontal and vertical
		getMovesInDirection(moves, board, coordinate, Direction(1, 0), 1);
		getMovesInDirection(moves, board, coordinate, Direction(-1, 0), 1);
		getMovesInDirection(moves, board, coordinate, Direction(0, 1), 1);
		getMovesInDirection(moves, board, coordinate, Direction(0, -1), 1);

		//diagonal
		getMovesInDirection(moves, board, coordinate, Direction(1, 1), 1);
		getMovesInDirection(moves, board, coordinate, Direction(-1, 1), 1);
		getMovesInDirection(moves, board, coordinate, Direction(1, -1), 1);
		getMovesInDirection(moves, board, coordinate, Direction(-1, -1), 1);

		return moves;
	}

    std::vector<Coordinate> findAdditionalMoves(const Coordinate& coordinate, const Board& board) 
    {
        std::vector<Coordinate> moves;

        std::vector<Coordinate> castleMoves = combination->getInitiatingMoves(board);
        for (int i = 0; i < castleMoves.size(); i++)
        {
            moves.push_back(castleMoves[i]);
        }

        return moves;
    }

    MoveSet* getMoveSet(const Coordinate& target, const Board& board)
    {
        MoveSet* moveSet = Piece::getMoveSet(target, board);

        //Process castling moves
        //TODO: needs fixing, castling doesnt work at the moment
        if (!moveSet) 
        {
            moveSet = combination->getCastlingMoveSet(board, target);
        }

        return moveSet;
    }

	CastleCombination* combination;

private:
};