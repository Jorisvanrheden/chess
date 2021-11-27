#pragma once

#include <iostream>
#include "Piece.h"

#include "MoveValidationManager.h"
#include "IMoveHandler.h"
#include "ISpecification.h"
#include "IFilter.h"
#include "IBoardAnalyzer.h"
#include "IBoardPopulator.h"
#include "IMoveSet.h"

class Board
{
public:
	Board(MoveValidationManager* validationManager, IMoveHandler* moveHandler, IFilter<Piece>* pieceFilter, IBoardAnalyzer* boardAnalyzer, IBoardPopulator* boardPopulator)
		: validationManager(validationManager), 
		  moveHandler(moveHandler), 
		  pieceFilter(pieceFilter),
		  boardAnalyzer(boardAnalyzer),
		  boardPopulator(boardPopulator)
	{
		//init empty board
		matrix = std::vector<std::vector<Piece*>>(boardPopulator->getWidth());
		for (int i = 0; i < boardPopulator->getWidth(); i++)
		{
			std::vector<Piece*> row(boardPopulator->getHeight());

			matrix[i] = row;
		}
	}
	~Board() {}

	void populate() 
	{
		boardPopulator->populate(*this);
	}

	void analyzeStatus(PLAYER_TYPE player) 
	{
		int playerStatus = boardAnalyzer->analyzeStatus(*this, player);

		if (playerStatus == 0) 
		{
			std::cout << "nothing happening" << std::endl;
		}
		if (playerStatus == 1)
		{
			std::cout << "CHECKED" << std::endl;
		}
		if (playerStatus == 2)
		{
			std::cout << "CHECKU MATUH" << std::endl;
		}
	}

	bool verifyMove(const Coordinate& origin, const Coordinate& target) 
	{
		std::vector<Coordinate> moves = getValidatedMoves(origin);

		for (const auto& move : moves) 
		{
			if (move == target) return true;
		}
		return false;
	}

	//return true if the piece has been succesfully moved 
	bool movePiece(const Coordinate& origin, const Coordinate& target)
	{
		if (origin == target) return false;

		Piece* piece = getPieceAt(origin);
		if (piece != NULL)
		{
			moveHandler->movePiece(*this, piece, origin, target);

			return true;
		}

		return false;
	}

	bool applyMoveSet(IMoveSet* moveSet) 
	{
		bool result = moveSet->move(*this);
		if (!result) return false;

		history.push_back(moveSet);

		return true;
	}

	IMoveSet* getMoveSet(const Coordinate& origin, const Coordinate& target) 
	{
		return moveHandler->getMoveSet(*this, origin, target);
	}

    std::vector<Coordinate> getBasicPieceMoves(const Coordinate& origin) const
    {
        Piece* piece = getPieceAt(origin);
        if (piece == NULL) return std::vector<Coordinate>();

        std::vector<Coordinate> moves = piece->findAvailableMoves(origin, *this);

        return getBoundaryValidatedMoves(origin, piece, moves);
    }
    
    //Pieces like the King have additional moves like castling. Moves are separated
    std::vector<Coordinate> getAllPieceMoves(const Coordinate& origin) const
    {
        Piece* piece = getPieceAt(origin);
        if (piece == NULL) return std::vector<Coordinate>();

        std::vector<Coordinate> moves = piece->findAvailableMoves(origin, *this);
        std::vector<Coordinate> additionalMoves = piece->findAdditionalMoves(origin, *this);

        moves.insert(moves.end(), additionalMoves.begin(), additionalMoves.end());

        return getBoundaryValidatedMoves(origin, piece, moves);
    }

    //Raw moves are moves for each piece that are
    //- The potential moves based on its movement ruleset
    //- Moves within the board
	std::vector<Coordinate> getRawMoves(const Coordinate& origin) const
	{
		Piece* piece = getPieceAt(origin);
		if (piece == NULL) return std::vector<Coordinate>();

		std::vector<Coordinate> rawMoves = getAllPieceMoves(origin);

		return rawMoves;
	}

    //Validated moves are moves for each piece that are
    //- Allowed given the logic of the validation manager (pieces in check/friendly fire) 
	std::vector<Coordinate> getValidatedMoves(const Coordinate& origin) 
	{
		Piece* piece = getPieceAt(origin);
		if (piece == NULL) return std::vector<Coordinate>();

        std::vector<Coordinate> rawMoves = getAllPieceMoves(origin);
		std::vector<Coordinate> logicValidatedMoves = getLogicValidatedMoves(origin, piece, rawMoves);

		return logicValidatedMoves;
	}

	bool isCoordinateValid(const Coordinate& coordinate) const
	{
		//Boundary checking
		if (coordinate.getX() < 0 || coordinate.getX() >= boardPopulator->getWidth()) return false;
		if (coordinate.getY() < 0 || coordinate.getY() >= boardPopulator->getHeight()) return false;

		return true;
	}

	int getSizeX() const
	{
		return boardPopulator->getWidth();
	}
	int getSizeY() const
	{
		return boardPopulator->getHeight();
	}

	void print() 
	{
		for (int j = 0; j < boardPopulator->getHeight(); j++)
		{
			for (int i = 0; i < boardPopulator->getWidth(); i++)
			{
				int id = 0;
				Piece* p = getPieceAt(Coordinate(i, j));
				if (p) id = p->getID();

				std::cout << id << ", ";	
			}

			std::cout << std::endl;
		}	

		std::cout << "\n\n\n" << std::endl;
	}

	std::vector<std::vector<int>> getBoardStatus(int playerID) 
	{
		std::vector<std::vector<int>> boardStatus(boardPopulator->getWidth(), std::vector<int>(boardPopulator->getHeight()));
		for (int i = 0; i < boardPopulator->getWidth(); i++)
		{
			for (int j = 0; j < boardPopulator->getHeight(); j++)
			{
				Piece* piece = getPieceAt(Coordinate(i, j));
				if (piece && piece->isSameType((PLAYER_TYPE)playerID)) 
				{
					boardStatus[i][j] = piece->getID();
				}
				else 
				{
					boardStatus[i][j] = 0;
				}
			}
		}

		return boardStatus;
	}

	std::vector<Piece*> filter(ISpecification<Piece>& specification) const
	{
		return pieceFilter->filter(getAllPieces(), specification);
	}

	Piece* getPieceAt(const Coordinate& coordinate) const
	{
		if (!isCoordinateValid(coordinate)) return NULL;

		return matrix[coordinate.getX()][coordinate.getY()];
	}

	void setPieceAt(const Coordinate& coordinate, Piece* piece)
	{
		if (!isCoordinateValid(coordinate)) return;

		matrix[coordinate.getX()][coordinate.getY()] = piece;

		//Not sure if I want this to be done here.
		//Also check whether it makes sense to have this coordinate history list per piece?
		if (piece != NULL)
		{
			//update the piece's coordinate history
			piece->addCoordinateToHistory(coordinate);
		}
	}

private:
	//Store the history of all movesets in the board
	std::vector<IMoveSet*> history;

	IFilter<Piece>* pieceFilter;
	IMoveHandler* moveHandler;
	MoveValidationManager* validationManager;
	IBoardAnalyzer* boardAnalyzer;
	IBoardPopulator* boardPopulator;

	std::vector<std::vector<Piece*>> matrix;

	std::vector<Piece*> getAllPieces() const
	{
		std::vector<Piece*> pieces;

		for (int j = 0; j < boardPopulator->getHeight(); j++)
		{
			for (int i = 0; i < boardPopulator->getWidth(); i++)
			{
				Piece* piece = getPieceAt(Coordinate(i, j));
				if (piece) pieces.push_back(piece);
			}
		}

		return pieces;
	}

    std::vector<Coordinate> getBoundaryValidatedMoves(const Coordinate& origin, Piece* piece, std::vector<Coordinate> moves) const
    {
        std::vector<Coordinate> validatedMoves;

        for (int i = 0; i < moves.size(); i++)
        {
            //make sure the coordinate is within the board
            if (!isCoordinateValid(moves[i])) continue;

            validatedMoves.push_back(moves[i]);
        }

        return validatedMoves;
    }

	std::vector<Coordinate> getLogicValidatedMoves(const Coordinate& origin, Piece* piece, std::vector<Coordinate> moves)
	{
		std::vector<Coordinate> validatedMoves;

		for (int i = 0; i < moves.size(); i++)
		{
			if (validationManager->isMoveValid(*this, piece, origin, moves[i]))
			{
				validatedMoves.push_back(moves[i]);
			}
		}

		return validatedMoves;
	}
};