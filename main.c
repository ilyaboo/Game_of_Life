#include <stdio.h>
#include "gfx.h"

int main() {
	int ysize = 800;
	int xsize = 800;

	char c;

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Example Graphics Program");

	// Set the current drawing color to green.
	gfx_color(0,200,100);

	// Draw a triangle on the screen.
	gfx_line(100,100,200,100);
	gfx_line(200,100,150,150);
	gfx_line(150,150,100,100);

	gfx_color(200,20,100);
	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();
		if (c == 'e') gfx_line(200,400,150,350);
		// Quit if it is the letter q.
		if(c=='q') break;
	}

	return 0;
}
