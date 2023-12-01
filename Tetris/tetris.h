#pragma once
#include <string>

class Board
{
private:
	int x;
	int y;
	char** board;
	char** board_buffer;

public:
	Board(int, int);
	~Board();
	//return width of the board
	int get_x() { return x; }
	//return height of the board
	int get_y() { return y; }
	//return a pointer to 2d char array
	char** get_board() { return board; }
	char** get_board_buffer() { return board_buffer; }
	friend std::ostream& operator<< (std::ostream&, const Board&);
	
};


class Block
{
private:
	int coord_x = 0;
	int coord_y = 1;
	int id;
	bool at_the_bottom = false;
	std::string block;
	int width = 0;
	int height = 0;

public:
	//takes in width and height of the board, in order to adjust coordinate range of where it can spawn to scale of the board
	Block(int, int);

	~Block() = default;

	//boolean, checks if the block is currently in motion or at the bottom
	bool is_atb() { return at_the_bottom; }

	//sets at_the_bottom flag to true
	void set_atb() { at_the_bottom = true; }

	//set block x coordinate
	void set_x(int x) { coord_x = x; }

	//set block y coordinate
	void set_y(int y) { coord_y = y; }

	//return block x coordinate
	int get_x() { return coord_x; }

	//return block y coordinate
	int get_y() { return coord_y; }

	//return block width
	int get_width() { return width; }

	//return block height
	int get_height() { return height; }

	void rotate();

	//returns string which contains shape of the block
	std::string get_block() { return block; }
};

class Shape 
{
private:
	int id;
	std::string shape;
public:
	Shape();
	~Shape() = default;
};