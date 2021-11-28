#pragma once

#include "Board.h"
#include "SamePlayerTypeSpecification.h"
#include "OtherPlayerTypeSpecification.h"
#include "PieceTypeSpecification.h"
#include "AndSpecification.h"

class SqaureAttackDetector
{
public:
    SqaureAttackDetector() {}

    bool isAttacked(const Board& board, const Coordinate& coordinate, PLAYER_TYPE player)
    {
        // - go through all other player types, and collect their boundary validated moves (not logic validated for reasons)
        OtherPlayerTypeSpecification otherPlayerTypeSpec(player);
        auto enemyPieces = board.filter(otherPlayerTypeSpec);
        for (const auto& enemyPiece : enemyPieces)
        {
            // - check if the piece's position is in one of those validated moves
            std::vector<Coordinate> enemyMoves = board.getBasicPieceMoves(enemyPiece->getCurrentCoordinate());

            if (isSquareAttacked(coordinate, enemyMoves)) return true;
        }

        return false;
    }

private:
    bool isSquareAttacked(const Coordinate& coordinate, std::vector<Coordinate> moves)
    {
        return (std::find(moves.begin(), moves.end(), coordinate) != moves.end());
    }
};