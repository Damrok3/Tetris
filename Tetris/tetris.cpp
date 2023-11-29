#include "tetris.h"
#include <iostream>
#include <random>

int generate_coord_x(int, int);

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

Board::~Board()
{
	for (int i = 0; i < this->y; i++)
	{
		delete[] board[i];
		delete[] board_buffer[i];
	}
	delete[] board;
	delete[] board_buffer;
}

Block::Block(int b_width, int b_height)
{
	std::srand(std::rand() ^ std::time(NULL));
	
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
			this->coord_x = generate_coord_x(b_width, 4);
			//this->coord_x = std::rand() % (b_width - 4) + 1;
			break;
		case 1: // J
			this->block =	"LLL      "
							"LLL      "
							"LLLLLLLLL"
							"LLLLLLLLL";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(b_width, 10);
			//this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 2: // L
			this->block =	"      %%%"
							"      %%%"
							"%%%%%%%%%"
							"%%%%%%%%%";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(b_width, 10);
			//this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 3: // O
			this->block =	"oooooo"
							"oooooo"
							"oooooo"
							"oooooo";
			this->width = 6;
			this->height = 4;
			this->coord_x = generate_coord_x(b_width, 7);
			//this->coord_x = std::rand() % (b_width - 7) + 1;
			break;
		case 4: // S
			this->block =	"   ssssss"
							"   ssssss"
							"ssssss   "
							"ssssss   ";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(b_width, 10);
			//this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 5: // Z
			this->block =	"zzzzzz   "
							"zzzzzz   "
							"   zzzzzz"
							"   zzzzzz";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(b_width, 10);
			//this->coord_x = std::rand() % (b_width - 10) + 1;
			break;
		case 6: // T
			this->block =	"   TTT   "
							"   TTT   "
							"TTTTTTTTT"
							"TTTTTTTTT";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(b_width, 10);
			//this->coord_x = std::rand() % (b_width - 10) + 1;
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

int generate_coord_x(int width, int b_size)
{
	std::srand(std::rand() ^ std::time(NULL));
	int random_nr = std::rand() % (width - b_size) + 1;
	int reminder = random_nr % 3;
	if (reminder != 0)
	{
		random_nr += (3 - reminder);
	}
	return random_nr;
}
