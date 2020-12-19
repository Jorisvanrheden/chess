#pragma once

#include "IPieceCheckDetector.h"
#include "Board.h"
#include "SamePlayerTypeSpecification.h"
#include "OtherPlayerTypeSpecification.h"
#include "PieceTypeSpecification.h"
#include "AndSpecification.h"

class PieceCheckDetector : public IPieceCheckDetector
{
public:
	PieceCheckDetector(PIECE_TYPE pieceType) : pieceType(pieceType)
	{

	}

	bool isChecked(const Board& board, PLAYER_TYPE player)
	{
		//analyze the board state:
		// - get the king (position) of the same type as piece
		SamePlayerTypeSpecification samePlayerTypeSpec(player);
		PieceTypeSpecification pieceTypeSpec(pieceType);
		AndSpecification<Piece> playerAndType(samePlayerTypeSpec, pieceTypeSpec);
		auto checkablePieces = board.filter(playerAndType);

		// - go through all other player types, and collect their boundary validated moves (not logic validated for reasons)
		OtherPlayerTypeSpecification otherPlayerTypeSpec(player);
		auto enemyPieces = board.filter(otherPlayerTypeSpec);
		for (auto& enemyPiece : enemyPieces)
		{
			// - check if the piece's position is in one of those validated moves
			std::vector<Coordinate> enemyMoves = board.getPieceBoundaryValidatedMoves(enemyPiece);

			for (auto& checkablePiece : checkablePieces)
			{
				if (isPieceChecked(checkablePiece, enemyMoves)) return true;
			}
		}

		return false;
	}

private:
	PIECE_TYPE pieceType;

	bool isPieceChecked(Piece* piece, std::vector<Coordinate> moves)
	{
		Coordinate coordinate = piece->getCurrentCoordinate();

		return (std::find(moves.begin(), moves.end(), coordinate) != moves.end());
	}
};