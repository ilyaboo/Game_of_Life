main: main.c
	gcc main.c gfx.c -o main -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lm