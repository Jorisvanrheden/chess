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
        //TODO: THIS NEEDS REFACTORING, just a test to see if this is feasible
        std::vector<Coordinate> moves = findAvailableMoves(getCurrentCoordinate(), board);

        for (const auto& move : moves)
        {
            if (move == target)
            {
                Piece* piece = board.getPieceAt(move);

                std::vector<MoveContent> content;
                std::vector<Piece*> targets;
                if (piece) targets.push_back(piece);

                content.push_back(MoveContent(this, getCurrentCoordinate(), move, targets));
                return new MoveSet(content);
            }
        }

        //Process castling moves
        return combination->getCastlingMoveSet(board, target);
    }

    std::vector<MoveSet*> transformMoves(const std::vector<Coordinate>& moves, const Board& board)
    {
        std::vector<MoveSet*> sets = Piece::transformMoves(moves, board);

        return sets;
    }

	CastleCombination* combination;

private:
};