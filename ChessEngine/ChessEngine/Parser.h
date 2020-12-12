#pragma once

#include <string>
#include <vector>
#include "Coordinate.h"
#include "GameConstants.h"
#include "Board.h"
#include "SamePlayerTypeSpecification.h"
#include "PieceTypeSpecification.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

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
	Parser(Board& board) : board(board) {}
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
				}

				continue;
			}

			PlayerMove move = parseMove(strings[i]);

			board.movePiece(move.from, move.to);
			board.print();

			//add to collection
			moves.push_back(move);
		}

		return context;
	}

	PlayerMove parseMove(const std::string& moveString) 
	{
		//start processing the string from position 0
		int iterator = 0;

		PIECE_TYPE type = getPieceType(moveString, iterator);
		int xSpecifier = getXComponent(moveString, iterator);
		bool isAttack = getIsMoveAttack(moveString, iterator);
		Coordinate target = getTargetCoordinate(moveString, iterator);
		Coordinate start = getStartCoordinate(target, moveString, type, xSpecifier);

		return PlayerMove(type, start, target);
	}

	int getXComponent(const std::string& moveString, int& iterator) 
	{
		//check if the current iteration is a lower case
		//if its a lower case, AND the next as well, we are dealing with an x-specifier
		int x = -1;
		if (std::islower(moveString[iterator]) && std::islower(moveString[iterator + 1]))
		{
			x = moveString[iterator] - 'a';
			iterator++;
		}

		return x;
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

	Coordinate getStartCoordinate(const Coordinate& target, const std::string& moveString, PIECE_TYPE pieceType, int xSpecifier)
	{
		PieceTypeSpecification pieceSpec(pieceType);

		auto piecesOfType = board.filter(pieceSpec);

		std::vector<Piece*> potentialPieces;

		//get the x, y components by going through board and checking which piece has the target in their available moves
		for (auto& piece : piecesOfType)
		{
			if (xSpecifier != -1) 
			{
				if (piece->getCurrentCoordinate().getX() != xSpecifier) continue;
			}

			std::vector<Coordinate> moves = board.getAvailableMoves(piece->getCurrentCoordinate());

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

			return Coordinate(x, y);
		}

		return Coordinate(0, 0);
	}

private:
		Board& board;

		bool containsMove(std::vector<Coordinate> moves, Coordinate move) 
		{
			for (int i = 0; i < moves.size(); i++) 
			{
				if (moves[i] == move) return true;
			}

			return false;
		}
};