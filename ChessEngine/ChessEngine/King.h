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

    std::vector<MoveSet> transformMoves(const std::vector<Coordinate>& moves, const Board& board)
    {
        std::vector<MoveSet> sets = Piece::transformMoves(moves, board);

        //TODO: also provide a target here?


        ////if the piece is a king, and the selected target is part of the castling routine
        ////then return a multiple moveset
        //if (piece->getID() == PIECE_TYPE::KING) 
        //{
        //	King* king = (King*)piece;

        //	MoveSet* castleMoveSet = king->combination->getCastlingMoveSet(board, target);
        //	if (castleMoveSet) return castleMoveSet;
        //}
        return std::vector<MoveSet>();
    }

	CastleCombination* combination;

private:
};