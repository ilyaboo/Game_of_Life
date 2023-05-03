#ifndef interface_h
#define interface_h

#include "params.h"
#include "gfx.h"

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

void fill_square_at_center_of_side(int x0, int y0, int square_side) {
	// function that fills the square area centered at (x0, y0)
	// with side square_side
	fill(x0 - square_side / 2, y0 - square_side / 2, x0 + square_side / 2, y0 + square_side / 2);
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

void draw_cross(int x0, int y0, int cross_side) {
	// draws a cross with top left corner at (x0, y0) that
	// can be drawn inside the square with side cross_side
	for (int i = 0; i <= cross_side / 6; i++) {
		gfx_line(x0 + i, y0, x0 + cross_side - cross_side / 6 + i, y0 + cross_side);
		gfx_line(x0 + i, y0 + cross_side, x0 + cross_side - cross_side / 6 + i, y0);
	}
}

void gen_start_button() {
	// function that generates the start button image
	// responsible for launching the simulation
	fill(button_x, start_button_y, button_x + large_button_width, start_button_y + button_height);
	gfx_color(0, 150, 57);
	fill_equilateral_triangle(button_x + 1.1 * side, start_button_y + 0.1 * side, 0.8 * side, 2);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_reset_button() {
	// function that generates the start button image
	// responsible for launching the simulation
	gfx_color(255, 85, 65);   // setting color to red
	fill(button_x, reset_button_y, button_x + large_button_width, reset_button_y + button_height);
	gfx_color(210, 70, 50);   // setting color to darker red
	draw_cross(button_x + 1.1 * side, reset_button_y + 0.1 * side, 0.8 * side);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_framerate_indicator_1() {
	// generates an indicator for framerate of 1
	gfx_color(0, 255, 0);   // setting color to green
	fill_square_at_center_of_side(button_x + 0.1 * large_button_width, framerate_indicators_y + 0.5 * side, 0.5 * side);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_framerate_indicator_2() {
	// generates an indicator for framerate of 2
	gfx_color(173, 255, 47);   // setting color to green
	fill_square_at_center_of_side(button_x + 0.3 * large_button_width, framerate_indicators_y + 0.5 * side, 0.5 * side);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_framerate_indicator_3() {
	// generates an indicator for framerate of 3
	gfx_color(255, 255, 0);   // setting color to green
	fill_square_at_center_of_side(button_x + 0.5 * large_button_width, framerate_indicators_y + 0.5 * side, 0.5 * side);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_framerate_indicator_4() {
	// generates an indicator for framerate of 4
	gfx_color(255, 165, 0);   // setting color to green
	fill_square_at_center_of_side(button_x + 0.7 * large_button_width, framerate_indicators_y + 0.5 * side, 0.5 * side);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_framerate_indicator_5() {
	// generates an indicator for framerate of 5
	gfx_color(255, 0, 0);   // setting color to green
	fill_square_at_center_of_side(button_x + 0.9 * large_button_width, framerate_indicators_y + 0.5 * side, 0.5 * side);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_framerate_indicators(int sleep_time) {
	// generates the framerate indicators according to the
	// current framerate_state
	gen_framerate_indicator_1();
	if (sleep_time < 1000000) {
		gen_framerate_indicator_2();
		if (sleep_time < 100000) {
			gen_framerate_indicator_3();
			if (sleep_time < 10000) {
				gen_framerate_indicator_4();
				if (sleep_time < 1000) {
					gen_framerate_indicator_5();
				}
			}
		}
	}
}

void gen_framerate_buttons() {
	// function that generates the framerate change buttons
	gfx_color(255, 200, 0);   // setting color to yellow
	fill(button_x, framerate_buttons_y, button_x + 1.2 * side, framerate_buttons_y + side);
	fill(button_x + 1.8 * side, framerate_buttons_y, button_x + 3 * side, framerate_buttons_y + side);
	gfx_color(204, 153, 0);
	fill_equilateral_triangle(button_x + 0.2 * side, framerate_buttons_y + side * 0.1, 0.8 * side, 3);
	fill_equilateral_triangle(button_x + 2 * side, framerate_buttons_y + side * 0.1, 0.8 * side, 1);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_preset1_button() {
	// function that generates the first preset button
	gfx_color(90, 90, 90);   // setting color to red
	fill(button_x, preset1_button_y, button_x + large_button_width, preset1_button_y + button_height);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_preset2_button() {
	// function that generates the second preset button
	gfx_color(90, 90, 90);   // setting color to red
	fill(button_x, preset2_button_y, button_x + large_button_width, preset2_button_y + button_height);
	gfx_color(0, 200, 100);   // resetting default color to green
}

void gen_preset3_button() {
	// function that generates the third preset button
	gfx_color(90, 90, 90);   // setting color to red
	fill(button_x, preset3_button_y, button_x + large_button_width, preset3_button_y + button_height);
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

void update_all(int sleep_time) {
	// function that updates all the interface according to the current
	// state of the field
	gfx_clear();
	gen_grid();
	gen_board();
	gen_start_button();
	gen_reset_button();
	gen_framerate_indicators(sleep_time);
	gen_framerate_buttons();
	gen_preset1_button();
	gen_preset2_button();
	gen_preset3_button();
	gfx_flush();
}

#endif