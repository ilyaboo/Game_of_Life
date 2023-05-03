#ifndef field_h
#define field_h

#include "params.h"

void empty_field() {
	// function that sets all values of the field matrix to zero
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			field[row][col] = 0;
		}
	}
}

int sleep_increase(int sleep_current) {
	// function that attempts to increase the sleep time (framerate)
	// returns updated sleep time
	if (sleep_current != 1000000) {
		return sleep_current * 10;
	} else {
		return sleep_current;
	}
}

int sleep_decrease(int sleep_current) {
	// function that attempts to decrease the sleep time (framerate)
	// returns updated sleep time
	if (sleep_current != 100) {
		return sleep_current / 10;
	} else {
		return sleep_current;
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

#endif