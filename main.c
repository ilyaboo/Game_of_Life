#include <stdio.h>
#include "gfx.h"

int main() {
	int ysize = 820;
	int xsize = 820;
	gfx_open(xsize,ysize,"Example Graphics Program");
	gfx_color(0,200,100);	
	
	// initializing field with zeros
	int field[10][10];
	


	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			gfx_line(80 * j + 10, 80 * i + 10, 80 * j + 10 + 80, 80 * i + 10);
			gfx_line(80 * j + 10 + 80, 80 * i + 10, 80 * j + 10 + 80, 80 * i + 10 + 80);
			gfx_line(80 * j + 10 + 80, 80 * i + 10 + 80, 80 * j + 10, 80 * i + 10 + 80);
			gfx_line(80 * j + 10, 80 * i + 10 + 80, 80 * j + 10, 80 * i + 10);
		}
	}
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
