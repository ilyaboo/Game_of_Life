#include <stdio.h>
#include "gfx.h"
#include <unistd.h>

const int max_epochs = 40;   // the maximum number of epochs after which the program stops
const int num_squares = 20;   // number of sqaures in a row/column
const int side = 30;   // length of the side of one square
const int margin = 10;   // margin between the field and edge of the window
int sleep_time = 5 * 100000;   // time for refreshing the field
int start_button_x = margin * 2 + side * num_squares;   // x position of the top left corner of the start button
int start_button_y = margin + side;   // y position of the top left corner of the start button
int start_button_width = 3 * side;   // width of the start button (multiple of side of the square)
int start_button_height = 1 * side;   // height of the start button (multiple of side of the square)
int reset_button_x = margin * 2 + side * num_squares;   // x position of the top left corner of the reset button
int reset_button_y = margin + 3 * side;   // y position of the top left corner of the reset button
int reset_button_width = 3 * side;   // width of the reset button (multiple of side of the square)
int reset_button_height = 1 * side;   // height of the reset button (multiple of side of the square)
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

void gen_start_button() {
	// function that generates the start button image
	// responsible for launching the simulation
	fill(start_button_x, start_button_y, start_button_x + start_button_width, start_button_y + start_button_height);
}

void gen_reset_button() {
	// function that generates the start button image
	// responsible for launching the simulation
	gfx_color(255, 85, 65);   // setting color to red
	fill(reset_button_x, reset_button_y, reset_button_x + reset_button_width, reset_button_y + reset_button_height);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void empty_field() {
	// function that sets all values of the field matrix to zero
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			field[row][col] = 0;
		}
	}
}

int update_field() {
	// function that updates the field matrix according to the rules
	// of Game of Life
	// returns 1 if made any updates, 0 otherwise
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

	// flag showing if there are any differences between old and new matrices
	int diff = 0;

	// updating the field
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			if (field[row][col] != new_field[row][col]) {
				diff = 1;
			}
			field[row][col] = new_field[row][col];
		}
	}
	return diff;
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

void update_all() {
	// function that updates all the interface according to the current
	// state of the field
	gfx_clear();
	gen_grid(num_squares, side, margin);
	gen_board();
	gen_start_button();
	gen_reset_button();
	gfx_flush();
}

int click_pos(int x, int y) {
	// function that outputs the place of the screen on which
	// the user clicked
	if ((x >= margin && x <= num_squares * side + margin) && (y >= margin && y <= num_squares * side + margin)) {
		// the user clicked on one of the squares on the field
		return 1;
	} else if ((x >= start_button_x && x <= start_button_x + start_button_width) &&\
	 (y >= start_button_y && y <= start_button_y + start_button_height)) {
		// the user clicked on the start button
		return 2;
	} else if ((x >= reset_button_x && x <= reset_button_x + reset_button_width) &&\
	 (y >= reset_button_y && y <= reset_button_y + reset_button_height)) {
		// the user clicked on the reset button
		return 3;
	} else {
		// missed any element of the interface
		return 0;
	}
}

int get_row(int x) {
	// function that returns the row of the field
	// corresponding to the entered x coordinate
	return (x - margin) / side;
}

int get_col(int y) {
	// function that returns the column of the field
	// corresponding to the entered y coordinate
	return (y - margin) / side;
}

int main() {
	int ysize = margin * 2 + side * num_squares;   // vertical size of the window
	int xsize = margin * 3 + side * num_squares + start_button_width;   // horizontal size of the window
	gfx_open(xsize, ysize, "Game of Life");   // creating the window
	gfx_color(0, 200, 100);   // setting default color to green
	
	// generating the grid for the field
	update_all();
	
	int click;
	while (1) {
		click = gfx_wait();
		if (click == 1) {
			int x = gfx_xpos();
			int y = gfx_ypos();
			int result = click_pos(x, y);
			if (result == 1) {
				// clicked on the field
				int row = get_row(x);
				int col = get_col(y);
				if (field[row][col] == 0) {
					field[row][col] = 1;   // if the field was empty
				} else {
					field[row][col] = 0;   // if the field was filled
				}
				update_all();
			} else if (result == 2) {
				// clicked on the start button
				int not_done = 1;
				int epoch_counter = 0;
				while (not_done && epoch_counter < max_epochs) {
					epoch_counter += 1;
					not_done = update_field();
					update_all();
					usleep(sleep_time);   // refresh field every 0.5 seconds
				}
			} else if (result == 3) {
				empty_field();
				update_all();
			}
		}
	}
	return 0;
}