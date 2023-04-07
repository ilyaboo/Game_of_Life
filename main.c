#include <stdio.h>
#include "gfx.h"

int num_squares = 10;   // number of sqaures in a row/column
static int side = 40;   // length of the side of one square
int margin = 10;   // margin between the field and edge of the window
int field[10][10];

void gen_grid(int num_squares, int side, int margin) {
	// function that generates a grid for the game field
	for (int i = 0; i < num_squares; ++i) {
		for (int j = 0; j < num_squares; ++j) {
			gfx_line(side * j + margin, side * i + margin, side * j + margin + side, side * i + margin);
			gfx_line(side * j + margin + side, side * i + margin, side * j + margin + side, side * i + margin + side);
			gfx_line(side * j + margin + side, side * i + margin + side, side * j + margin, side * i + margin + side);
			gfx_line(side * j + margin, side * i + margin + side, side * j + margin, side * i + margin);
		}
	}
}

void fill(int x0, int y0, int x1, int y1) {
	// function that fills the rectangular area betwen
	// points (x0, y0) and (x1, y1) with color
	for (int col = x0; col <= x1; ++col) {
		gfx_line(col, y0, col, y1);
	}
}

void fill_square(int x0, int y0) {
	// function that fills the square area with top left corner
	// at (x0, y0) and with side side with color
	fill(x0, y0, x0 + side, y0 + side);
}

void fill_square_at_location(int row, int col) {
	// function that fills the square in the given location
	// on the field with color
	fill_square(margin + row * side, margin + col * side);
}

void empty_field() {
	// function that sets all values of the field matrix to zero
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			field[row][col] = 0;
		}
	}
}

void gen_board() {
	// function that inspects the contents of field matrix
	// and generates a visual representation of it on the game field
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			// printf("row: %d, col: %d \n", row, col);
			if (field[row][col] == 1) {
				fill_square_at_location(row, col);
			}
		}
	}
}

int main() {
	int ysize = margin * 2 + side * num_squares;   // vertical size of the window
	int xsize = margin * 2 + side * num_squares;   // horizontal size of the window
	gfx_open(xsize, ysize, "Game of Life");
	gfx_color(0, 200, 100);	
	
	// initializing field with zeros
	empty_field();
	field[1][1] = 1;
	field[2][3] = 1;
	field[0][0] = 1;
	field[9][9] = 1;
	
	// generating the grid for the field
	gen_grid(num_squares, side, margin);
	gen_board();

	char c;
	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();
		if (c == 'e') gfx_line(200,400,150,350);
		// Quit if it is the letter q.
		if(c=='q') break;
	}

	return 0;
}
