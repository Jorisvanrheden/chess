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

#include "PieceCollection.h"

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
	PlayerMoveSet(std::vector<IMoveSet*> moves) : moves(moves) {}

	//size indicates player size
	std::vector<IMoveSet*> moves;
};

struct MoveContext
{
	std::vector<IMoveSet*> playerMoveSets;
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

		std::vector<IMoveSet*> moves;

		//moves can be split using the "1." or "2." strings
		for (int i = 0; i < strings.size(); i++) 
		{
			//if we encounter an iteration, we move to the next turn
			if (strings[i].find('.') != std::string::npos) 
			{
				if (moves.size() > 0) 
				{
					//context.playerMoveSets.push_back(PlayerMoveSet(moves));
					moves.clear();

					std::cout << "MOVE NUMBER: " << context.playerMoveSets.size() << std::endl;
				}

				continue;
			}

			//check if the string is a special move and can be processed by the board
			IMoveSet* moveSet = getCastlingMoveSet(strings[i]);
	
			if (moveSet) 
			{
				moves.push_back(moveSet);
			}

			if (!moveSet)
			{
				PlayerMove move = parseMove(strings[i]);
				moveSet = new MoveSetSingle(move.from, move.to);
			}

			playerSelector.moveSet(moveSet);

			board.print();
		}

		return context;
	}

	IMoveSet* getCastlingMoveSet(const std::string& move) 
	{
		if (move == "O-O" || move == "O-O")
		{
			PieceTypeSpecification pieceSpec(PIECE_TYPE::KING);
			SamePlayerTypeSpecification playerSpec(playerSelector.getActivePlayer());
			AndSpecification<Piece> andSpec(pieceSpec, playerSpec);

			auto kings = board.filter(andSpec);
			for (const auto& king : kings)
			{
				King* kingPiece = (King*)king;

				if (move == "O-O")
				{
					return kingPiece->combination->getMoveSetShortCastle();
				}
				else if (move == "O-O-O")
				{
					return kingPiece->combination->getMoveSetLongCastle();
				}
			}
		}

		return NULL;
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

			std::vector<Coordinate> moves = board.getValidatedMoves(piece->getCurrentCoordinate());

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
};