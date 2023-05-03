#ifndef params_h
#define params_h

// general game parameters
#define max_epochs 50   // the maximum number of epochs after which the program stops, default: 50
#define num_squares 40   // number of sqaures in a row/column, default: 40

// display parameters
#define side 15   // length of the side of one square, default: 15
#define margin 10   // margin between the field and edge of the window, default: 10

// display parameters for buttons
#define start_button_width 3 * side   // width of the start button (multiple of side of the square)
#define start_button_height side   // height of the start button (multiple of side of the square)
#define start_button_x  2 * margin + side * num_squares   // x position of the top left corner of the start button
#define start_button_y margin + side   // y position of the top left corner of the start button
#define reset_button_width 3 * side   // width of the reset button (multiple of side of the square)
#define reset_button_height side   // height of the reset button (multiple of side of the square)
#define reset_button_x margin * 2 + side * num_squares   // x position of the top left corner of the reset button
#define reset_button_y margin + 3 * side   // y position of the top left corner of the reset button
#define framerate_indicators_y margin + 5 * side // y position of the set of framerate adjustment indicators
#define framerate_buttons_y margin + 6 * side // y position of the pair of framerate adjustment buttons
#define preset_button_width 3 * side   // width of the preset buttons (multiple of side of the square)
#define preset_button_height side   // height of the preset buttons (multiple of side of the square)
#define preset_button_x margin * 2 + side * num_squares   // x position of the top left corner of the preset buttons
#define preset1_button_y margin + 8 * side   // y position of the top left corner of the first preset button
#define preset2_button_y margin + 10 * side   // y position of the top left corner of the second preset button
#define preset3_button_y margin + 12 * side   // y position of the top left corner of the third preset button
int field[num_squares][num_squares];

#endif