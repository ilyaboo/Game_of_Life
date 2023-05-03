#ifndef presets_h
#define presets_h

#include "params.h"
#include "field.h"

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

#endif