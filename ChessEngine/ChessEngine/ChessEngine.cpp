#include <iostream>
#include "Board.h"
#include "DefaultBoardPopulator.h"

int main()
{
	//To setup the most basic game, we need to do the following;

	//- create board
	//	- initialize board size
	//	- initialize pieces (new position)

	Board board;
	board.load(new DefaultBoardPopulator());

	//print default
	//board.print();

	Coordinate pawnPos(3, 1);
	Coordinate origin(1, 0);

	std::vector<Coordinate> availablePositionsA = board.getAvailableMoves(pawnPos);
	board.movePiece(pawnPos, availablePositionsA[0]);


	std::vector<Coordinate> availablePositions = board.getAvailableMoves(origin);
	if (availablePositions.size() > 0) 
	{
		board.movePiece(origin, availablePositions[0]);
	}
	/*for (int i = 0; i < availablePositions.size(); i++) 
	{
		availablePositions[i].print();
	}*/

	//print result
	board.print();

	getchar();
	return 0;
}
