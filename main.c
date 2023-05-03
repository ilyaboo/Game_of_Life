///////////////////////////////////////
///////////// HEADERS /////////////////
///////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include "gfx.h"



///////////////////////////////////////
//////////// PARAMETERS ///////////////
///////////////////////////////////////

// general game parameters
#define max_epochs 50   // the maximum number of epochs after which the program stops, default: 50
#define num_squares 40   // number of sqaures in a row/column, default: 40

// display parameters
#define side 15   // length of the side of one square, default: 15
#define margin 10   // margin between the field and edge of the window, default: 10

// display parameters for buttons
#define start_button_width 3 * side   // width of the start button (multiple of side of the square)
#define start_button_height side   // height of the start button (multiple of side of the square)
#define start_button_x  2 * margin + side * num_squares   // x position of the top left corner of the start button
#define start_button_y margin + side   // y position of the top left corner of the start button
#define reset_button_width 3 * side   // width of the reset button (multiple of side of the square)
#define reset_button_height side   // height of the reset button (multiple of side of the square)
#define reset_button_x margin * 2 + side * num_squares   // x position of the top left corner of the reset button
#define reset_button_y margin + 3 * side   // y position of the top left corner of the reset button
#define preset_button_width 3 * side   // width of the preset buttons (multiple of side of the square)
#define preset_button_height side   // height of the preset buttons (multiple of side of the square)
#define preset_button_x margin * 2 + side * num_squares   // x position of the top left corner of the preset buttons

#define framerate_buttons_y margin + 6 * side

#define preset1_button_y margin + 8 * side   // y position of the top left corner of the first preset button
#define preset2_button_y margin + 10 * side   // y position of the top left corner of the second preset button
#define preset3_button_y margin + 12 * side   // y position of the top left corner of the third preset button
int field[num_squares][num_squares];



///////////////////////////////////////
//////// INTERFACE FUNCTIONS //////////
///////////////////////////////////////

void gen_grid() {
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
	// at (x0, y0) and with side "side" with color
	fill(x0, y0, x0 + side, y0 + side);
}

void fill_square_at_location(int row, int col) {
	// function that fills the square in the given location
	// on the field with color
	fill_square(margin + row * side, margin + col * side);
}

void draw_triangle(int xtl, int ytl, int xbr, int ybr, int direction) {
    int x1, y1, x2, y2, x3, y3; // vertices of isosceles triangle (x1, y1), (x2, y2), (x3, y3)
    // Calculate the three vertices of the isosceles triangle based on the direction
    switch (direction) {
        case 1: // upward looking triangle
            x1 = (int) ((xtl + xbr) / 2);
            y1 = ytl;
            x2 = xtl;
            y2 = ybr;
            x3 = xbr;
            y3 = ybr;
            break;
        case 2: // triangle looking to the right
            x1 = xtl;
            y1 = ytl;
            x2 = xbr;
            y2 = (int) ((ytl + ybr) / 2);
            x3 = xtl;
            y3 = ybr;
            break;
        case 3: // downward looking triangle
            x1 = xtl;
            y1 = ytl;
            x2 = xbr;
            y2 = ytl;
            x3 = (int) ((xtl + xbr) / 2);
            y3 = ybr;
            break;
        case 4: // triangle looking to the left
            x1 = xbr;
            y1 = ytl;
            x2 = xbr;
            y2 = ybr;
            x3 = xtl;
            y3 = (int) ((ytl + ybr) / 2);
            break;
    }

    // drawing the sides of the triangle
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x3, y3);
    gfx_line(x3, y3, x1, y1);
}

void fill_triangle(int x0, int y0, int x1, int y1, int direction) {
	// function that fill an area of triangular shape with color
	while (x0 <= x1 && y0 <= y1) {
		draw_triangle(x0, y0, x1, y1, direction);
		x0 += 1;
		y0 += 1;
		x1 -= 1;
		y1 -= 1;
	}
}

void fill_equilateral_triangle(int x0, int y0, int triangle_side, int direction) {
	// function that fills the area corresponding to equilateral triangle with side 
	// triangle_side with color
	fill_triangle(x0, y0, x0 + triangle_side, y0 + triangle_side, direction);
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

void gen_framerate_buttons() {
	// function that generates the framerate change buttons
	gfx_color(255, 200, 0);   // setting color to yellow
	fill(preset_button_x, framerate_buttons_y, preset_button_x + 1.2 * side, framerate_buttons_y + side);
	fill(preset_button_x + 1.8 * side, framerate_buttons_y, preset_button_x + 3 * side, framerate_buttons_y + side);
	gfx_color(204, 153, 0);
	fill_equilateral_triangle(preset_button_x + 0.2 * side, framerate_buttons_y + side * 0.1, 0.8 * side, 3);
	fill_equilateral_triangle(preset_button_x + 2 * side, framerate_buttons_y + side * 0.1, 0.8 * side, 1);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_preset1_button() {
	// function that generates the first preset button
	gfx_color(90, 90, 90);   // setting color to red
	fill(preset_button_x, preset1_button_y, preset_button_x + preset_button_width, preset1_button_y + preset_button_height);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_preset2_button() {
	// function that generates the second preset button
	gfx_color(90, 90, 90);   // setting color to red
	fill(preset_button_x, preset2_button_y, preset_button_x + preset_button_width, preset2_button_y + preset_button_height);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_preset3_button() {
	// function that generates the third preset button
	gfx_color(90, 90, 90);   // setting color to red
	fill(preset_button_x, preset3_button_y, preset_button_x + preset_button_width, preset3_button_y + preset_button_height);
	gfx_color(0, 200, 100);   // resetting default color to green
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
	gen_grid();
	gen_board();
	gen_start_button();
	gen_reset_button();
	gen_framerate_buttons();
	gen_preset1_button();
	gen_preset2_button();
	gen_preset3_button();
	gfx_flush();
}



///////////////////////////////////////
/// INTEFACE INTERACTION FUNCTIONS ////
///////////////////////////////////////

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
	} else if ((x >= reset_button_x && x <= reset_button_x + 1.2 * side) &&\
	 (y >= framerate_buttons_y && y <= framerate_buttons_y + reset_button_height)) {
		// the user clicked on the decrease frameraet button
		return 4;
	} else if ((x >= reset_button_x + 1.8 * side && x <= reset_button_x + 3 * side) &&\
	 (y >= framerate_buttons_y && y <= framerate_buttons_y + reset_button_height)) {
		// the user clicked on the increase framerate button
		return 5;
	} else if ((x >= preset_button_x && x <= preset_button_x + preset_button_width) &&\
	 (y >= preset1_button_y && y <= preset1_button_y + preset_button_height)) {
		// the user chose preset 1
		return 6;
	} else if ((x >= preset_button_x && x <= preset_button_x + preset_button_width) &&\
	 (y >= preset2_button_y && y <= preset2_button_y + preset_button_height)) {
		// the user chose preset 2
		return 7;
	} else if ((x >= preset_button_x && x <= preset_button_x + preset_button_width) &&\
	 (y >= preset3_button_y && y <= preset3_button_y + preset_button_height)) {
		// the user chose preset 3
		return 8;
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



///////////////////////////////////////
////////// FIELD FUNCTIONS ////////////
///////////////////////////////////////

void empty_field() {
	// function that sets all values of the field matrix to zero
	for (int row = 0; row < num_squares; ++row) {
		for (int col = 0; col < num_squares; ++col) {
			field[row][col] = 0;
		}
	}
}

void preset1() {
	// function that modifies the field matrix according to the first preset
	empty_field();
	field[4][3] = 1;
	field[5][4] = 1;
	field[3][5] = 1;
	field[4][5] = 1;
	field[5][5] = 1;
}

void preset2() {
	// function that modifies the field matrix according to the second preset
	empty_field();
	field[0][5] = 1;
	field[1][5] = 1;
	field[0][6] = 1;
	field[1][6] = 1;
	field[12][4] = 1;
	field[12][5] = 1;
	field[12][6] = 1;
	field[12][7] = 1;
	field[12][8] = 1;
	field[13][3] = 1;
	field[13][5] = 1;
	field[13][6] = 1;
	field[13][7] = 1;
	field[13][9] = 1;
	field[14][4] = 1;
	field[14][8] = 1;
	field[15][5] = 1;
	field[15][6] = 1;
	field[15][7] = 1;
	field[16][6] = 1;
	field[20][4] = 1;
	field[21][4] = 1;
	field[22][3] = 1;
	field[22][5] = 1;
	field[23][2] = 1;
	field[23][3] = 1;
	field[23][5] = 1;
	field[23][6] = 1;
	field[24][1] = 1;
	field[24][7] = 1;
	field[25][4] = 1;
	field[26][1] = 1;
	field[26][2] = 1;
	field[26][6] = 1;
	field[26][7] = 1;
	field[29][5] = 1;
	field[30][5] = 1;
	field[31][6] = 1;
	field[34][3] = 1;
	field[34][4] = 1;
	field[35][3] = 1;
	field[35][4] = 1;
}

void preset3() {
	// function that modifies the field matrix according to the third preset
	empty_field();
	field[0][5] = 1;
	field[1][5] = 1;
	field[0][6] = 1;
	field[1][6] = 1;
	field[12][4] = 1;
	field[12][5] = 1;
	field[12][6] = 1;
	field[12][7] = 1;
	field[12][8] = 1;
	field[13][3] = 1;
	field[13][5] = 1;
	field[13][6] = 1;
	field[13][7] = 1;
	field[13][9] = 1;
	field[14][4] = 1;
	field[14][8] = 1;
	field[15][5] = 1;
	field[15][6] = 1;
	field[15][7] = 1;
	field[16][6] = 1;
	field[20][4] = 1;
	field[21][4] = 1;
	field[22][3] = 1;
	field[22][5] = 1;
	field[23][2] = 1;
	field[23][3] = 1;
	field[23][5] = 1;
	field[23][6] = 1;
	field[24][1] = 1;
	field[24][7] = 1;
	field[25][4] = 1;
	field[26][1] = 1;
	field[26][2] = 1;
	field[26][6] = 1;
	field[26][7] = 1;
	field[29][5] = 1;
	field[30][5] = 1;
	field[31][6] = 1;
	field[34][3] = 1;
	field[34][4] = 1;
	field[35][3] = 1;
	field[35][4] = 1;
	field[33][21] = 1;
	field[33][22] = 1;
	field[34][21] = 1;
	field[34][23] = 1;
	field[35][23] = 1;
	field[36][23] = 1;
	field[36][24] = 1;
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



///////////////////////////////////////
/////////// MAIN FUNCTION /////////////
///////////////////////////////////////

int main() {
	int sleep_time = 4 * 10000;   // time for refreshing the field in microseconds, default: 0.4s
	int ysize = margin * 2 + side * num_squares;   // vertical size of the window
	int xsize = margin * 3 + side * num_squares + start_button_width;   // horizontal size of the window
	gfx_open(xsize, ysize, "Game of Life");   // creating the window
	gfx_color(0, 200, 100);   // setting default color to green
	update_all();   // generating the grid for the field
	while (1) {
		int click = gfx_wait();   // reading user's input
		if (click == 1) {   // if user clicked with LMB
			int x = gfx_xpos();   // obtaining the coordinates of the point on which user clicked
			int y = gfx_ypos();
			int result = click_pos(x, y);   // identify the element on which user clicked
			int row, col, not_done, epoch_counter;

			switch (result) {
			case 1:
				// clicked on the field
				row = get_row(x);
				col = get_col(y);
				if (field[row][col] == 0) {
					field[row][col] = 1;   // if the field was empty
				} else {
					field[row][col] = 0;   // if the field was filled
				}
				update_all();
				break;
			
			case 2:
				// clicked on the start button
				not_done = 1;
				epoch_counter = 0;
				while (not_done && epoch_counter < max_epochs) {
					epoch_counter += 1;
					not_done = update_field();
					update_all();
					usleep(sleep_time);   // refresh field according to framerate
				}
				break;

			case 3:
				// clicked on the reset button
				empty_field();
				update_all();
				break;
			
			case 4:
				// clicked on framerate decrease button
				break;

			case 5:
				// clicked on framerate increase button
				break;
			
			case 6:
				// clicked on the first preset button
				preset1();
				update_all();
				break;
			
			case 7:
				// clicked on the second preset button
				preset2();
				update_all();
				break;

			case 8:
				// clicked on the third preset button
				preset3();
				update_all();
				break;

			default:
				break;
			}
		}
	}
	return 0;
}