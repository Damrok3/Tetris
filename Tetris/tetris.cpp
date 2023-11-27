#include "tetris.h"
#include <iostream>
#include <random>

Board::Board(int x, int y)
{
	this->board = new char*[y];
	this->board_buffer = new char* [y];
	for (int i = 0; i < y; i++)
	{
		this->board[i] = new char[x];
		this->board_buffer[i] = new char[x];
	}
	this->x = x;
	this->y = y;
	for (int i = 0; i < this->y; i++)
	{
		for (int j = 0; j < this->x; j++)
		{
			if (i == 0 || i == this->y - 1)
			{
				board[i][j] = '-';
				board_buffer[i][j] = '-';
			}
			else if (j == 0 || j == this->x - 1)
			{
				board[i][j] = '|';
				board_buffer[i][j] = '|';
			}
			else
			{
				board[i][j] = ' ';
				board_buffer[i][j] = ' ';
			}
		}
	}
}

Block::Block(int b_width, int b_height)
{
	std::srand(std::time(NULL));
	this->id = std::rand() % 7;

	switch (this->id)
	{
		case 0: // I
			this->block =	"***" 
							"***"
							"***"
							"***"
							"***"
							"***";
			this->width = 3;
			this->height = 6;
			this->coord_x = std::rand() % (b_width - 4) + 1;
			break;
		case 1: // J
			this->block =	"ooo      "
							"ooo      "
							"ooooooooo"
							"ooooooooo";
			this->width = 9;
			this->height = 4;
			this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 2: // L
			this->block =	"      ooo"
							"      ooo"
							"ooooooooo"
							"ooooooooo";
			this->width = 9;
			this->height = 4;
			this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 3: // O
			this->block =	"oooooo"
							"oooooo"
							"oooooo"
							"oooooo";
			this->width = 6;
			this->height = 4;
			this->coord_x = std::rand() % (b_width - 7) + 1;
			break;
		case 4: // S
			this->block =	"   oooooo"
							"   oooooo"
							"oooooo   "
							"oooooo   ";
			this->width = 9;
			this->height = 4;
			this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 5: // Z
			this->block =	"oooooo   "
							"oooooo   "
							"   oooooo"
							"   oooooo";
			this->width = 9;
			this->height = 4;
			this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 6: // T
			this->block =	"   ooo   "
							"   ooo   "
							"ooooooooo"
							"ooooooooo";
			this->width = 9;
			this->height = 4;
			this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
	}
}

std::ostream & operator<<(std::ostream& os, const Board& b)
{
	for (int i = 0; i < b.y; i++)
	{
		for (int j = 0; j < b.x; j++)
		{
			os << b.board[i][j];
		}
		os << std::endl;
	}
	return os;
}

