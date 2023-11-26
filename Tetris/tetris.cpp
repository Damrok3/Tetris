#include "tetris.h"
#include <iostream>

Board::Board(int x, int y)
{
	this->x = x;
	this->y = y;
	for (int i = 0; i < this->y; i++)
	{
		for (int j = 0; j < this->x; j++)
		{
			if (i == 0 || i == this->y - 1)
			{
				board += '-';
			}
			else if (j == 0 || j == this->x - 1)
			{
				board += "|";
			}
			else
			{
				board += " ";
			}
		}
		board += "\n";
	}
}

std::ostream & operator<<(std::ostream& os, const Board& b)
{
	return os << b.board;
}

