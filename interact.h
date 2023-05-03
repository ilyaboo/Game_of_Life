#ifndef interact_h
#define interact_h

#include "params.h"

int click_pos(int x, int y) {
	// function that outputs the place of the screen on which
	// the user clicked
	if ((x >= margin && x <= num_squares * side + margin) && (y >= margin && y <= num_squares * side + margin)) {
		// the user clicked on one of the squares on the field
		return 1;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= start_button_y && y <= start_button_y + button_height)) {
		// the user clicked on the start button
		return 2;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= reset_button_y && y <= reset_button_y + button_height)) {
		// the user clicked on the reset button
		return 3;
	} else if ((x >= button_x && x <= button_x + 1.2 * side) &&\
	 (y >= framerate_buttons_y && y <= framerate_buttons_y + button_height)) {
		// the user clicked on the decrease frameraet button
		return 4;
	} else if ((x >= button_x + 1.8 * side && x <= button_x + 3 * side) &&\
	 (y >= framerate_buttons_y && y <= framerate_buttons_y + button_height)) {
		// the user clicked on the increase framerate button
		return 5;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= preset1_button_y && y <= preset1_button_y + button_height)) {
		// the user chose preset 1
		return 6;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= preset2_button_y && y <= preset2_button_y + button_height)) {
		// the user chose preset 2
		return 7;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= preset3_button_y && y <= preset3_button_y + button_height)) {
		// the user chose preset 3
		return 8;
    } else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= preset4_button_y && y <= preset4_button_y + button_height)) {
		// the user chose preset 4
		return 9;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= preset5_button_y && y <= preset5_button_y + button_height)) {
		// the user chose preset 5
		return 10;
	} else if ((x >= button_x && x <= button_x + large_button_width) &&\
	 (y >= preset6_button_y && y <= preset6_button_y + button_height)) {
		// the user chose preset 6
		return 11;
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

#endif