#include <stdio.h>
#include <unistd.h>
#include "gfx.h"
#include "params.h"
#include "interface.h"
#include "interact.h"
#include "presets.h"

int main() {
	int sleep_time = 10000;   // time for refreshing the field in microseconds
	int ysize = margin * 2 + side * num_squares;   // vertical size of the window
	int xsize = margin * 3 + side * num_squares + large_button_width;   // horizontal size of the window
	gfx_open(xsize, ysize, "Game of Life");   // creating the window
	gfx_color(0, 200, 100);   // setting default color to green
	update_all(sleep_time);   // generating the grid for the field
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
				update_all(sleep_time);
				break;
			
			case 2:
				// clicked on the start button
				not_done = 1;
				epoch_counter = 0;
				while (not_done && epoch_counter < max_epochs) {
					epoch_counter += 1;
					not_done = update_field();
					update_all(sleep_time);
					usleep(sleep_time);   // refresh field according to framerate
				}
				break;

			case 3:
				// clicked on the reset button
				empty_field();
				update_all(sleep_time);
				break;
			
			case 4:
				// clicked on framerate decrease button
				// equivalent to increase in sleep time
				sleep_time = sleep_increase(sleep_time);
				update_all(sleep_time);
				break;

			case 5:
				// clicked on framerate increase button
				// equivalent to decrease in sleep time
				sleep_time = sleep_decrease(sleep_time);
				update_all(sleep_time);
				break;
			
			case 6:
				// clicked on the first preset button
				preset1();
				update_all(sleep_time);
				break;
			
			case 7:
				// clicked on the second preset button
				preset2();
				update_all(sleep_time);
				break;

			case 8:
				// clicked on the third preset button
				preset3();
				update_all(sleep_time);
				break;

			case 9:
				// clicked on the fourth preset button
				preset4();
				update_all(sleep_time);
				break;
			
			case 10:
				// clicked on the fifth preset button
				preset5();
				update_all(sleep_time);
				break;

			case 11:
				// clicked on the sixth preset button
				preset6();
				update_all(sleep_time);
				break;

			default:
				break;
			}
		}
	}
	return 0;
}