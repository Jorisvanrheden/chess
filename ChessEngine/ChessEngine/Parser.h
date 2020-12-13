#pragma once

#include <string>
#include <vector>
#include "Coordinate.h"
#include "GameConstants.h"
#include "Board.h"
#include "IPlayerSelector.h"
#include "SamePlayerTypeSpecification.h"
#include "PieceTypeSpecification.h"
#include "AndSpecification.h"

#include "MoveSetSingle.h"
#include "MoveSetMultiple.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

#include <time.h>

struct PlayerMove 
{
public:
	PlayerMove(PIECE_TYPE type, const Coordinate& from, const Coordinate& to) : type(type), from(from), to(to) {}
	~PlayerMove() {}

	PIECE_TYPE type;
	Coordinate from;
	Coordinate to;
};

struct PlayerMoveSet
{
public:
	PlayerMoveSet(std::vector<PlayerMove> moves) : moves(moves) {}

	//size indicates player size
	std::vector<PlayerMove> moves;
};

struct MoveContext
{
	std::vector<PlayerMoveSet> playerMoveSets;
};

class Parser
{
public:
	Parser(Board& board, IPlayerSelector& playerSelector) : board(board), playerSelector(playerSelector) {}
	~Parser() {}

	MoveContext parse(const std::string& filepath)
	{
		std::ifstream file(filepath);
		std::string line;

		while (std::getline(file, line)) 
		{
			if (line.rfind("1.", 0) == 0) 
			{
				return parseGame(line);
			}
		}

		return MoveContext();
	}

	MoveContext parseGame(std::string gameString) 
	{
		std::vector<std::string> strings;
		std::istringstream stream(gameString);

		std::string string;
		while (std::getline(stream, string, ' ')) 
		{
			strings.push_back(string);
		}
		//first split the string up in moves per turn



		MoveContext context;

		std::vector<PlayerMove> moves;

		//moves can be split using the "1." or "2." strings
		for (int i = 0; i < strings.size(); i++) 
		{
			//if we encounter an iteration, we move to the next turn
			if (strings[i].find('.') != std::string::npos) 
			{
				if (moves.size() > 0) 
				{
					context.playerMoveSets.push_back(PlayerMoveSet(moves));
					moves.clear();

					std::cout << "MOVE NUMBER: " << context.playerMoveSets.size() << std::endl;
				}

				continue;
			}

			if (strings[i] == "O-O" || strings[i] == "O-O-O")
			{
				//hard code castling for now
				PieceTypeSpecification kingSpec(PIECE_TYPE::KING);
				SamePlayerTypeSpecification playerSpec(playerSelector.getActivePlayer());
				AndSpecification<Piece> andSpec(kingSpec, playerSpec);

				PieceTypeSpecification rookSpec(PIECE_TYPE::ROOK);
				AndSpecification<Piece> andSpec2(rookSpec, playerSpec);

				//get the king that is about to castle
				auto king = board.filter(andSpec);

				//get the rooks 
				auto rooks = board.filter(andSpec2);

				IMoveSet* moveSet = castle(strings[i], king, rooks);
				playerSelector.moveSet(moveSet);
				//board.print();
			}
			else 
			{
				PlayerMove move = parseMove(strings[i]);

				MoveSetSingle singleMove(move.from, move.to);
				playerSelector.moveSet(&singleMove);
				//board.print();

				//add to collection
				moves.push_back(move);
			}
		}

		return context;
	}

	PlayerMove parseMove(const std::string& moveString) 
	{
		//start processing the string from position 0
		int iterator = 0;

		PIECE_TYPE type = getPieceType(moveString, iterator);
		Coordinate xyComponent = getXYComponent(moveString, iterator);
		bool isAttack = getIsMoveAttack(moveString, iterator);
		Coordinate target = getTargetCoordinate(moveString, iterator);
		Coordinate start = getStartCoordinate(target, moveString, type, xyComponent);

		return PlayerMove(type, start, target);
	}

	Coordinate getXYComponent(const std::string& moveString, int& iterator) 
	{
		//check if the current iteration is a lower case
		//if its a lower case, AND the next as well, we are dealing with an x-specifier
		int x = -1;
		int y = -1;

		if (moveString[iterator] != 'x') 
		{
			if (std::islower(moveString[iterator]) && std::islower(moveString[iterator + 1]))
			{
				x = moveString[iterator] - 'a';
				iterator++;
			}

			if (std::isdigit(moveString[iterator]) && std::islower(moveString[iterator + 1])) 
			{
				y = moveString[iterator] - '0';
				y = board.getSizeY() - y;
				//white starts at the bottom by default, so the y is inverted

				iterator++;
			}
		}
		
		return Coordinate(x, y);
	}

	bool getIsMoveAttack(const std::string& moveString, int& iterator) 
	{
		if (iterator < moveString.size()) 
		{
			if (moveString[iterator] == 'x') 
			{
				iterator++;
				return true;
			}
		}

		return false;
	}

	PIECE_TYPE getPieceType(const std::string& moveString, int& iterator)
	{
		//if the string does not start with a capital, it's a pawn,
		//otherwise it's a piece
		PIECE_TYPE type = PIECE_TYPE::PAWN;

		if (moveString.size() > 0) 
		{
			if (std::isupper(moveString[0]))
			{
				iterator++;

				switch (moveString[0]) 
				{
				case 'K':
					return PIECE_TYPE::KING;
				case 'Q':
					return PIECE_TYPE::QUEEN;
				case 'N':
					return PIECE_TYPE::KNIGHT;
				case 'B':
					return PIECE_TYPE::BISHOP;
				case 'R':
					return PIECE_TYPE::ROOK;
				}
			}
		}

		return type;
	}

	Coordinate getStartCoordinate(const Coordinate& target, const std::string& moveString, PIECE_TYPE pieceType, Coordinate xyComponent)
	{
		PieceTypeSpecification pieceSpec(pieceType);
		SamePlayerTypeSpecification playerSpec(playerSelector.getActivePlayer());
		AndSpecification<Piece> andSpec(pieceSpec, playerSpec);

		auto piecesOfType = board.filter(andSpec);

		std::vector<Piece*> potentialPieces;

		//get the x, y components by going through board and checking which piece has the target in their available moves
		for (auto& piece : piecesOfType)
		{
			if (xyComponent.getX() != -1)
			{
				if (piece->getCurrentCoordinate().getX() != xyComponent.getX()) continue;
			}
			if (xyComponent.getY() != -1)
			{
				if (piece->getCurrentCoordinate().getY() != xyComponent.getY()) continue;
			}

			std::vector<Coordinate> moves = playerSelector.getAvailableMoves(piece->getCurrentCoordinate());

			if (containsMove(moves, target)) potentialPieces.push_back(piece);
		}

		
		if (potentialPieces.size() == 1) 
		{
			return potentialPieces[0]->getCurrentCoordinate();
		}
		else 
		{
			std::cout << "This should not happen" << std::endl;
		}

		return Coordinate(0, 0);
	}

	Coordinate getTargetCoordinate(const std::string& moveString, int& iterator)
	{
		//we need two properties, so we check for size() - 1
		if (iterator < moveString.size() - 1) 
		{
			int x = moveString[iterator] - 'a';
			int y = moveString[iterator + 1] - '0';
			//white starts at the bottom by default, so the y is inverted

			y = board.getSizeY() - y;

			return Coordinate(x, y);
		}

		return Coordinate(0, 0);
	}

private:
		Board& board;
		IPlayerSelector& playerSelector;

		bool containsMove(std::vector<Coordinate> moves, Coordinate move) 
		{
			for (int i = 0; i < moves.size(); i++) 
			{
				if (moves[i] == move) return true;
			}

			return false;
		}

		IMoveSet* castle(const std::string& moveString, std::vector<Piece*> kings, std::vector<Piece*> rooks) 
		{
			for (auto& rook : rooks)
			{
				int kingFrom = 4;
				int kingTo = 0;

				int rookFrom = 0;
				int rookTo = 0;

				if (moveString == "O-O") 
				{
					kingTo = 6;
					rookFrom = 7;
					rookTo = 5;
				}
				else if (moveString == "O-O-O") 
				{
					kingTo = 2;
					rookFrom = 0;
					rookTo = 3;
				}

				if (rook->getCurrentCoordinate().getX() != rookFrom) continue;

				std::vector<std::tuple<Coordinate, Coordinate>> multipleMoves;

				Coordinate kingOrigin(kingFrom, kings[0]->getCurrentCoordinate().getY());
				Coordinate kingTarget(kingTo, kings[0]->getCurrentCoordinate().getY());

				Coordinate rookOrigin(rookFrom, rook->getCurrentCoordinate().getY());
				Coordinate rookTarget(rookTo, rook->getCurrentCoordinate().getY());

				multipleMoves.push_back(std::tuple<Coordinate, Coordinate>{kingOrigin, kingTarget});
				multipleMoves.push_back(std::tuple<Coordinate, Coordinate>{rookOrigin, rookTarget});

				return new MoveSetMultiple(multipleMoves);
			}	
		}
};