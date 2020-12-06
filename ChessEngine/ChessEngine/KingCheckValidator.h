#pragma once

#include "IMoveValidator.h"

#include "PieceTypeSpecification.h"
#include "OtherPlayerTypeSpecification.h"	
#include "SamePlayerTypeSpecification.h"	
#include "AndSpecification.h"

class KingCheckValidator : public IMoveValidator
{
	bool isMoveValid(const Board& board, Piece* piece, const Coordinate& origin, const Coordinate& target)
	{
		//copy the board state
		Board copy = Board(board);

		//apply the the move to the piece onto the copied board
		copy.movePiece(origin, target);

		//analyze the board state:
		// - get the king (position) of the same type as piece
		SamePlayerTypeSpecification samePlayerTypeSpec(piece->getPlayerType());
		PieceTypeSpecification pieceTypeSpec(PIECE_TPYE::KING);
		AndSpecification<Piece> playerAndType(samePlayerTypeSpec, pieceTypeSpec);
		auto kings = copy.filter(playerAndType);

		// - go through all other player types, and collect their boundary validated moves (not logic validated for reasons)
		OtherPlayerTypeSpecification otherPlayerTypeSpec(piece->getPlayerType());
		auto enemyPieces = copy.filter(otherPlayerTypeSpec);
		for (auto& enemyPiece : enemyPieces) 
		{
			// - check if the king's position is in one of those validated moves
			std::vector<Coordinate> enemyMoves = copy.getPieceBoundaryValidatedMoves(enemyPiece);
			
			for (auto& king : kings) 
			{
				//if the king is checked, the move is not valid
				if (checkIfMovesContainKing(king, enemyMoves)) return false;
			}
		}
		
		//move is valid
		return true;
	}
	
private:
	bool checkIfMovesContainKing(Piece* king, std::vector<Coordinate> moves) 
	{
		Coordinate kingCoordinate = king->getCurrentCoordinate();

		return (std::find(moves.begin(), moves.end(), kingCoordinate) != moves.end());
	}
};