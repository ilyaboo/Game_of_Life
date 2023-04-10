game_of_life: main.c
	gcc main.c gfx.c -o game_of_life -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lm