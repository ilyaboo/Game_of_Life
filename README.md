# Conway's Game of Life

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

## Installation

Clone this repository using the following command:

```
$ git clone https://github.com/ilyaboo/game_of_life.git
```
Navigate to the project directory and compile the program using the Makefile:

```
$ cd game_of_life
$ make
```

## Starting the program

To launch the program, run the compiled binary:

```
$ ./game_of_life
```

## 
