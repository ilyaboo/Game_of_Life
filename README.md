# Conway's Game of Life

![intro](https://user-images.githubusercontent.com/108785038/231083639-af67405b-abd0-45bb-b79a-36b8b078ec22.gif)

This is a C program that implements [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). The program allows the user to select the initial alive cells manually as well as to select one of the presets.

## Background information

Conway's Game of Life (classified as a cellular automaton) is a game that simulates the evolution of the cells. The player can interact with the field in order to create the initial configuration of the cells. The evolution of this configuration is then simulated by the game and does not require any user input. That is why the game is sometimes called [zero-player game](https://en.wikipedia.org/wiki/Zero-player_game).

## Rules of the game

The game consists of a two-dimensional grid of squares, each representing one cell. The sell can be either dead (empty) or alive (filled with color). The future state of each cell is determined by its neighbors – cells that are adjacent to it vertically, horizontally, and diagonally (total of 8 cells). The game itslf consists of the simulation of the evolution of the cells, which is visualized by consequent updates of the game field. Each field update is done by determining the new state of each cell on the field according to the following rules.
#### If the cell was alive:
- If the cell has fewer than 2 live neighbors, it dies, as if by underpopulation.
- If the cell has 2 or 3 live neighbors, it lives on to the next generation.
- If the cell has more than 3 live neighbors, it dies, as if by overpopulation.
#### If the cell was dead:
- If the cell has exactly 3 live neighbors, it becomes a live cell, as if by reproduction.
- If the number of live neighbors is not equal to 3, it remains dead.

The game continues updating the field with newer generations of the cells by applying the rules listed above to each cell of the previous generation.

## Implementation

### Relevant libraries

In order to implement the game I used the following libraries (headers).
- **stdio.h** – standard C library for input/output
- **unistd.h** – standard C library needed for setting the field refresh rate
- **gfx.h** – [graphics library](https://www3.nd.edu/~dthain/courses/cse20211/fall2013/gfx/) needed for all the graphics of the project
```c
#include <stdio.h>
#include <unistd.h>
#include "gfx.h"
```
*Notice the **gfx.c** and **gfx.h** files in the repository needed for the **gfx** library to work*

### Parameters

The code starts with a number of global variables. They affect the behaviour of the program as well as some display properties. These variables are grouped in the following categories.

#### General game parameters
```c
const int max_epochs = 50;   // the maximum number of epochs after which the program stops, default: 50
const int num_squares = 40;   // number of sqaures in a row/column, default: 40
const int sleep_time = 4 * 100000;   // time for refreshing the field in microseconds, default: 0.4s
```
These parameters affect the general game mechanics. By changing `max_epochs` one can change the maximum number of generations the program will process until it stops. `num_squares` is responsible for the number of squares that fit the width/height of the square field. Finally, `sleep_time` is the time before the program updates the field to the new one. The time is measured in microseconds and is set to 0.4s by default.

#### Display parameters
```c
const int side = 15;   // length of the side of one square, default: 15
const int margin = 10;   // margin between the field and edge of the window, default: 10
```
These parameters are responsible for visual representation of the field. `side` is the side of one cell in pixels, whereas `margin` is the distance between the edge of the window and the field measured in pixels.

#### Display parameters for buttons

These parameters set the coordinates of the top left corner of each button, as well as the size of each button. For example, here are the corresponding parameters for the "start" button.
```c
const int start_button_width = 3 * side;
const int start_button_height = 1 * side;
const int start_button_x = margin * 2 + side * num_squares;
const int start_button_y = margin + side;
```
Even though some of these parameters repeat themselves, I intentionally left them like that in order to be able to adjust button positions and sizes.

### Functions

Functions I used in the code are can be grouped in the following categories.
#### Interface functions
Interface functions use the gfx library and are used to manipulate the interface of the program. Most of these function utilize the helper function `void fill(x1, y1, x2, y2)`, which fills the rectangular area between points `(x1, y1)` and `(x2, y2)` with color. Other functions in these categories include other helper functions, which simplify the use of the "fill" function, functions that generate buttons, `void gen_board()` function that reads from the `field` 2D array to display its current state, and `void update_all()` function that applies all the changes made to the board.
#### Interface interaction functions
These are used to process user input. This section has a `int click_pos(int x, int y)` function that identifies on which part of the interface did the user click. Helper functions `int get_row(int x)` and `int get_col(int y)` help identify the cell on which the user clicked.
#### Field functions
These manipulate the `field` 2D arrray. These include `void empty_field()` which sets all the values of the array to zeros, preset functions, which set the `field` state according to the provided preset, as well as the `int update_field()` which updates the `field` by one generation accoring to the rules of game. Notice that this function treats the field as a confined area, making the cells on one edge of the field adjacent to the ones on the opposite side of the field. This implementation enhances the game experience while still allowing the user to explore classical patterns.

### Main function

`int main()` starts with initialization of `ysize` and `xsize`, which are the height and the width of the program window respectively.
```c
int ysize = margin * 2 + side * num_squares;
int xsize = margin * 3 + side * num_squares + start_button_width;
```
Notice that both integers are calculated dynamically depending on some of the parameters defined in the beginning of the program. This allows the size of the window to perfectly fit all the elements of the interface.
Then a program window with the calculated dimensions is created by the following line of code.
```c
gfx_open(xsize, ysize, "Game of Life");
```
Then the default color is set to green.
```c
gfx_color(0, 200, 100);
```
Finally, the call for the `update_all()` function makes all the interface elements appear in the window.
```c
update_all();
```
The program then inters an infinite loop which reads user's input – a click of the left mouse button (LMB) on one of the interface elements.
```c
int click = gfx_wait();
```
The program then calls the ```click_pos()``` function to evaluate the click.
```c
int result = click_pos(x, y);
```
The program will then adjust the interface according to the result of the evaluation. Options include adding or removing the cell from the initial setup, resetting the setup, loading one of the presets, and launching the simulation. Notice that active simulation will either finish after creating a maximum number of generations of generations specified in the beginning of the program, or when it detects that the field reached a static state.

## Installation

Clone this repository by entering the following command in the terminal:

```bash
$ git clone https://github.com/ilyaboo/game_of_life.git
```
Navigate to the project directory and compile the program using the Makefile:

```bash
$ cd game_of_life
$ make
```

## Starting the program

To launch the program, run the compiled binary:

```bash
$ ./game_of_life
```

## 
