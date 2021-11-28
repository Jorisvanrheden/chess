#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const PLAYER_TYPE& type, Direction direction) 
		: Piece(type), direction(direction) 
	{}
	~Pawn() {}

	PIECE_TYPE getID()
	{
		return PIECE_TYPE::PAWN;
	}

    void addEnPassantSet(std::vector<MoveSet*>& sets, const Board& board)
    {
        //En passant checks apply when:
        //- the enemy pawn is one space next to this pawn
        //- the previous move on the board was a PAWN that moved up two spaces
        //- is ENEMY PAWN
        std::vector<MoveSet*> history = board.getHistory();

        if (history.size() == 0) return;

        MoveSet* move = history[history.size() - 1];

        //Move count should be 1
        if (move->getMoveCount() > 1) return;

        //Should be ENEMY PAWN
        Piece* target = board.getPieceAt(move->getTarget(0));
        if (target->getID() != PIECE_TYPE::PAWN) return;
        if (target->getPlayerType() == getPlayerType()) return;

        //First check if the enemy pawn is right next to this pawn
        if (move->getTarget(0).getX() != getCurrentCoordinate().getX()) return;

        //Move distance should be the pawn double move
        //First hard code it for vertical moves
        Coordinate moveDiff = move->getMoveDiff(0);
        if (moveDiff.getY() != DISTANCE_FIRST_MOVE) return;

        //return the position behind the target pawn
        int targetX = move->getTarget(0).getX();
        int targetY = move->getTarget(0).getY() + direction.getY() * DISTANCE_DEFAULT;

        std::vector<MoveContent> content;
        content.push_back(MoveContent(this, getCurrentCoordinate(), Coordinate(targetX, targetY), { target }));

        MoveSet* set = new MoveSet(content);
        sets.push_back(set);
    }

    void addEnPassantMoves(std::vector<Coordinate>& moves, const Board& board) 
    {
        //En passant checks apply when:
        //- the enemy pawn is one space next to this pawn
        //- the previous move on the board was a PAWN that moved up two spaces
        //- is ENEMY PAWN
        std::vector<MoveSet*> history = board.getHistory();

        if (history.size() == 0) return;

        MoveSet* move = history[history.size() - 1];

        //Move count should be 1
        if (move->getMoveCount() > 1) return;

        //Should be ENEMY PAWN
        Piece* piece = board.getPieceAt(move->getTarget(0));
        if (piece->getID() != PIECE_TYPE::PAWN) return;
        if (piece->getPlayerType() == getPlayerType()) return;

        //First check if the enemy pawn is right next to this pawn
        if (abs(move->getTarget(0).getX() - getCurrentCoordinate().getX()) != 1) return;

        //Move distance should be the pawn double move
        //First hard code it for vertical moves
        Coordinate moveDiff = move->getMoveDiff(0);
        if (moveDiff.getY() != DISTANCE_FIRST_MOVE) return;

        //return the position behind the target pawn
        int targetX = move->getTarget(0).getX();
        int targetY = move->getTarget(0).getY() + direction.getY() * DISTANCE_DEFAULT;
        
        moves.push_back(Coordinate(targetX, targetY));
    }

	std::vector<Coordinate> findAvailableMoves(const Coordinate& coordinate, const Board& board)
	{
		//A pawn can only move up or down (depending on it's type)
		std::vector<Coordinate> moves;

		//pawns are different in the sense that their movement vector does not equal the attack vector
		//they move only up and down, but attack diagonally
		//there both types of moves should be included in the available move set

		//pawns can move 2 units in a straight direction if they haven't been moved yet
		int moveDistance = (coordinateHistory.size() > 1) ? DISTANCE_DEFAULT : DISTANCE_FIRST_MOVE;
		getMovesInDirection(moves, board, coordinate, direction, moveDistance, false);

		//pawns can attack diagonally, but only with a distance of 1
		//to the the diagonal, we get the perpendicular directions
		std::vector<Direction> perpendicularDirections = Direction::getPerpendicularDirections(direction);
		for (const auto& perpendicular : perpendicularDirections)
		{
			//also add the direction for one unit, otherwise we'd be checking next to the pawn, not diagonally
			int x = coordinate.getX() + direction.getX() + perpendicular.getX();
			int y = coordinate.getY() + direction.getY() + perpendicular.getY();

			Coordinate targetCoordinate(x, y);
			Piece* targetPiece = board.getPieceAt(targetCoordinate);

			if (targetPiece) 
			{
				moves.push_back(targetCoordinate);
			}
		}

        addEnPassantMoves(moves, board);

		return moves;
	}

    std::vector<MoveSet*> transformMoves(const std::vector<Coordinate>& moves, const Board& board)
    {
        std::vector<MoveSet*> sets = Piece::transformMoves(moves, board);

        addEnPassantSet(sets, board);

        return sets;
    }

private:

    const int DISTANCE_DEFAULT = 1;
    const int DISTANCE_FIRST_MOVE = 2;

	Direction direction;
};