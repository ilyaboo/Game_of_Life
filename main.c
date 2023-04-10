#include <stdio.h>
#include "gfx.h"
#include <unistd.h>

const int num_squares = 20;   // number of sqaures in a row/column
static int side = 40;   // length of the side of one square
int margin = 10;   // margin between the field and edge of the window
int field[num_squares][num_squares];

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

void update_field() {
	// function that updates the field matrix according to the rules
	// of Game of Life
	int new_field[num_squares][num_squares];
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			// counter for number of alive cells around
			int counter = 0;

			// arrays for rows and columns surrounding the cell
			int rows[3] = {0, row, 0};
			int cols[3] = {0, col, 0};

			// checking if we are on the top row of the field
			if (row == 0) {
				rows[0] = num_squares - 1;
			} else {
				rows[0] = row - 1;
			}

			// checking if we are on the bottom row of the field
			if (row == num_squares - 1) {
				rows[2] = 0;
			} else {
				rows[2] = row + 1;
			}

			// checking if we are on the leftmost column
			if (col == 0) {
				cols[0] = num_squares - 1;
			} else {
				cols[0] = col - 1;
			}

			// checking if we are on the rightmost column
			if (col == num_squares - 1) {
				cols[2] = 0;
			} else {
				cols[2] = col + 1;
			}

			// counting the number of adjacent cells alive
			for (int r = 0; r < 3; ++r) {
				for (int c = 0; c < 3; ++c) {
					counter += field[rows[r]][cols[c]];
				}
			}

			// subtracting the value of the cell itself
			counter -= field[row][col];

			// if cell is dead
			if (field[row][col] == 0) {
				// checking if the cell is reproducing
				if (counter == 3) {
					new_field[row][col] = 1;
				} else {
					new_field[row][col] = 0;
				}
				
			} else {
				// check if dies due to underpopulation
				if (counter < 2) {
					new_field[row][col] = 0;
				// check if dies due to overpopulation
				} else if (counter > 3) {
					new_field[row][col] = 0;
				// survives otherwise
				} else {
					new_field[row][col] = 1;
				}
			}

		}
	}

	// updating the field
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			field[row][col] = new_field[row][col];
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
	field[3][3] = 1;
	field[4][3] = 1;
	field[9][9] = 1;
	
	// generating the grid for the field
	gen_grid(num_squares, side, margin);
	gen_board();
	
	while (1) {
		gfx_clear();
		update_field();
		gen_board();
		gen_grid(num_squares, side, margin);
		gfx_flush();
		sleep(1);
	}
	/*
	char c;
	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();
		if (c == 'e') gfx_line(200,400,150,350);
		// Quit if it is the letter q.
		if(c=='q') break;
	}
	*/
	return 0;
}
