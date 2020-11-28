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

	std::vector<Coordinate> availablePositions = board.getAvailableMoves(Coordinate(5, 5));
	for (int i = 0; i < availablePositions.size(); i++) 
	{
		availablePositions[i].print();
	}

	getchar();
	return 0;
}
