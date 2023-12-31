#include <iostream>
#include "tetris.h"
#include <vector>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <conio.h>

void block_update(Board&, Block*&);
void board_update(Board&, Block*&);
void setCursorPosition(int, int);
void setConsoleCursorVisibility(bool);
void check_for_down_arrow_press();
inline int get_arrow_key_input();
void score_control(Board&, char**);

////stuff for checking exec times vvv
//auto start = std::chrono::high_resolution_clock::now();
//...
//auto end = std::chrono::high_resolution_clock::now();
//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//std::cout << "exec time: " << duration.count() << std::endl;

std::chrono::milliseconds timespan(200);
int score = 0;
bool game_over = false;

int main()
{
	setConsoleCursorVisibility(false);

	Board board(32, 42);
	Block* block = nullptr;
	//main loop
	while (!game_over)
	{
		block_update(board, block);
		board_update(board, block);
		setCursorPosition(0, 0);
		std::cout << board << "your score is : " << score << "!\n" << std::flush;
		check_for_down_arrow_press();
		std::this_thread::sleep_for(timespan);
	}
	std::cout << "Game Over!\nPress enter to exit";
	std::cin.get();

	return 0;
}

void board_update(Board& b, Block*& block)
{
	char** board = b.get_board();
	char** board_buffer = b.get_board_buffer();
	for (int i = 0; i < b.get_height(); i++)
	{
		for (int j = 0; j < b.get_width(); j++)
		{
			board[i][j] = board_buffer[i][j];
		}
	}
	if (block != nullptr && block->is_atb() == false)
	{
		int block_y = block->get_y();
		int block_x = block->get_x();
		int block_width = block->get_width();
		int block_height = block->get_height();
		std::string block_str = block->get_block();
		int index = 0;
		for (int y = block_y; y < block_y + block_height; y++)
		{
			for (int x = block_x; x < block_x + block_width; x++)
			{
				if (block_str[index] != ' ')
				{
					board[y][x] = block_str[index];
				}
				index++;
			}
		}
	}
	if (block != nullptr && block->is_atb())
	{
		score_control(b, board);
	}
}

void score_control(Board& b, char** board)
{
	if (int row = b.check_if_score())
	{
		score++;
		std::string temp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 1; j < b.get_width() - 1; j++)
			{
				temp += board[row][j];
				board[row][j] = 219;
				board[row - 1][j] = 219;
			}
			setCursorPosition(0, 0);
			std::cout << b << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			for (int j = 1; j < b.get_width() - 1; j++)
			{
				board[row][j] = temp[j];
				board[row - 1][j] = temp[j];
			}
			setCursorPosition(0, 0);
			std::cout << b << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		b.remove_line(row);
		score_control(b, board);
	}
}

void block_update(Board& b, Block*& block)
{
	int input = get_arrow_key_input();
	int i = 0;
	// all blocks are on the bottom, time to generate a new one
	if (block == nullptr || block->is_atb())
	{
		if (block != nullptr && block->is_atb() && block->get_y() == 1)
		{
			delete block;
			game_over = true;
			
		}
		else
		{
			delete block;
			block = new Block(b.get_width(), b.get_height());
		}
	}
	//block still in the air
	else 
	{

		if (block->get_y() < b.get_height() - block->get_height() - 1 && !block->check_if_block_intersects(b, 0))
		{
			block->set_y(block->get_y() + 1);
			if (input != 0)
			{
				switch (input)
				{
					case 75:
						if(block->get_x() > 3 && !block->check_if_block_intersects(b, 1))
							block->set_x(block->get_x() - 3);
						break;
					case 77:
						if (block->get_x() < b.get_width() - block->get_width() - 2 && !block->check_if_block_intersects(b, 2))
							block->set_x(block->get_x() + 3);
						break;
					case 72:
						block->rotate(b.get_width());
						break;
				}
			}
		}
		else
		{
			block->set_atb();
			char** board_buffer = b.get_board_buffer();
			char** board = b.get_board();
			for (int i = 0; i < b.get_height(); i++)
			{
				for (int j = 0; j < b.get_width(); j++)
				{
					board_buffer[i][j] = board[i][j];
				}
			}
		}
	}
}

void setCursorPosition(int x , int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void setConsoleCursorVisibility(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void check_for_down_arrow_press()
{
	if (GetAsyncKeyState(VK_DOWN) != 0)
	{
		timespan = std::chrono::milliseconds(20);
	}
	else
	{
		timespan = std::chrono::milliseconds(200);
	}
}

inline int get_arrow_key_input()
{
	int input = 0;
	//when the key is pressed
	if (_kbhit())	
	{
		//take the input
		input = _getch(); 

		//arrow keys return value twice because they're special keys, get rid of that
		if (input == 224)
		{
			input = _getch(); 
		}
		//consume any additional key presses stuck in the input buffer
		while (_kbhit())
		{
			_getch(); 
		}
	}
	return input;
}