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

    struct EnPassantData 
    {
        Coordinate targetCoordinate;
        Piece* targetPiece;

        EnPassantData(Coordinate targetCoordinate, Piece* targetPiece) 
            : targetCoordinate(targetCoordinate), targetPiece(targetPiece)
        {
        
        }
    };

    EnPassantData* getEnPassantData(const Board& board) 
    {
        //En passant checks apply when:
        //- the enemy pawn is one space next to this pawn
        //- the previous move on the board was a PAWN that moved up two spaces
        //- is ENEMY PAWN
        std::vector<MoveSet*> history = board.getHistory();

        if (history.size() == 0) return NULL;

        MoveSet* move = history[history.size() - 1];

        //Move count should be 1
        if (move->getMoveCount() > 1) return NULL;

        //Should be ENEMY PAWN
        Piece* target = board.getPieceAt(move->getTarget(0));
        if (target->getID() != PIECE_TYPE::PAWN) return NULL;
        if (target->getPlayerType() == getPlayerType()) return NULL;

        //First check if the enemy pawn is right next to this pawn
        if (abs(move->getTarget(0).getX() - getCurrentCoordinate().getX()) != 1) return NULL;
        if (abs(move->getTarget(0).getY() - getCurrentCoordinate().getY()) != 0) return NULL;

        //Move distance should be the pawn double move
        //First hard code it for vertical moves
        Coordinate moveDiff = move->getMoveDiff(0);
        if (moveDiff.getY() != DISTANCE_FIRST_MOVE) return NULL;

        //return NULL the position behind the target pawn
        int targetX = move->getTarget(0).getX();
        int targetY = move->getTarget(0).getY() + direction.getY() * DISTANCE_DEFAULT;
        Coordinate targetCoordinate(targetX, targetY);
 
        return new EnPassantData(targetCoordinate, target);
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

        //Process en passant moves
        EnPassantData* data = getEnPassantData(board);
        if (data) 
        {
            moves.push_back(data->targetCoordinate);
        }

		return moves;
	}

    MoveSet* getMoveSet(const Coordinate& target, const Board& board)
    {
        MoveSet* moveSet = Piece::getMoveSet(target, board);

        //Process en passant
        EnPassantData* data = getEnPassantData(board);
        if (data) 
        {
            //Overwrite data where possible?
            //TODO: check how to do this nicely
            for (int i = 0; i < moveSet->getMoveCount(); i++)
            {
                MoveContent content = moveSet->getContent(i);

                if (content.to == data->targetCoordinate)
                {
                    moveSet->setContent(i, { data->targetPiece });
                }
            }
        }

        return moveSet;
    }

private:

    const int DISTANCE_DEFAULT = 1;
    const int DISTANCE_FIRST_MOVE = 2;

	Direction direction;
};