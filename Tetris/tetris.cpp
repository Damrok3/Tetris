#include "tetris.h"
#include <iostream>
#include <random>

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

Block::Block(int b_width, int b_height)
{
	std::srand(std::time(NULL));
	this->id = std::rand() % 8;

	switch (this->id)
	{
		case 0: // I
			this->block =	"***\n" 
							"***\n"
							"***\n"
							"***\n"
							"***\n"
							"***\n";
			this->coord_x = std::rand() % (b_width - 2);
			break;
		case 1: // J
			this->block =	"ooo\n"
							"ooo\n"
							"ooooooooo\n"
							"ooooooooo\n";
			this->coord_x = std::rand() % (b_width - 8);
			break;
		case 2: // L
			this->block =	"      ooo\n"
							"      ooo\n"
							"ooooooooo\n"
							"ooooooooo\n";
			this->coord_x = std::rand() % (b_width - 8);
			break;
		case 3: // O
			this->block =	"oooooo\n"
							"oooooo\n"
							"oooooo\n"
							"oooooo\n";
			this->coord_x = std::rand() % (b_width - 5);
			break;
		case 5: // S
			this->block =	"   oooooo\n"
							"   oooooo\n"
							"oooooo   \n"
							"oooooo   \n";
			this->coord_x = std::rand() % (b_width - 8);
			break;
		case 6: // Z
			this->block =	"oooooo   \n"
							"oooooo   \n"
							"   oooooo\n"
							"   oooooo\n";
			this->coord_x = std::rand() % (b_width - 8);
			break;
		case 7: // T
			this->block =	"   ooo   \n"
							"   ooo   \n"
							"ooooooooo\n"
							"ooooooooo\n";
			this->coord_x = std::rand() % (b_width - 8);
			break;
	}
}

std::ostream & operator<<(std::ostream& os, const Board& b)
{
	return os << b.board;
}

