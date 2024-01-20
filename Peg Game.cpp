/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Linux x86_64 and G++
    Author: George Maratos and David Hayes + Martin Laugesen
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move(string);
void initialize_board();
bool game_over(string);
bool valid_move(string);


int main()
{
  string move_input = "ACG";
  initialize_board();
  display_instructions();
  display_board();
  
  while (game_over(move_input) != true) {
    cout << "Enter positions from, jump, and to (e.g. EFG): ";
    cin >> move_input;
    
    if (move_input.size() == 3) {
      for (int i = 0; i < 3; i++) {
        if (move_input.at(i) >= 97 && move_input.at(i) <= 109) {
          move_input.at(i) -= 32;
        }
      }
    }

    if (game_over(move_input)) {
      return 0;
    }
    
    make_move(move_input);

    if (game_over(move_input)) {
      return 0;
    }

    display_board();
  }
}

bool game_over(string move_input)
{
  /* TODO: Write a function that returns true only if there is one
  one peg left, or if the user gives up by entering 'X' (or 'x')*/
  int num_pegs = 0;

  //checks each position for a peg
  for (char position = 'A'; position <= 'M'; position++) {
    char cell = get_element(position);
    if (cell == '#') {
      num_pegs++;
    }
  }

  //if there is one peg left it will mean the game is over
  if (num_pegs <= 1) {
    cout << "Congrats you win!";
    return true;
  }

  //checks if user gave up
  else if (move_input == "X" || move_input == "x") {
    cout << "Exiting.";
    return true;
  }
  
  return false;
}

void initialize_board()
{
  /* TODO: Initialize the board to have all pegs, besides the very
  center hole.  ONLY use the functions get_element and set_element
  to update  the board,  do not access  the array 'board' directly.
  */
  for (char position = 'A'; position <= 'M'; position++) {
    set_element(position, '#');
  }

  set_element('G', '.');
}

bool valid_move(string move_input) {
  bool ok_move = false;

  //checks input is correct length
  if (move_input.size() != 3) {
    cout << "*** Invalid sequence. Please retry.";
    return ok_move;
  }

  //checks each letter is in range A-M
  for (int i = 0; i < 3; i++) {
      if (move_input.at(i) < 'A' || move_input.at(i) > 'M') {
        cout << "*** Given move has positions not on the board! Please retry.";
        return ok_move;
      }
  }

  //gets the board value at each input letter
  char element1 = get_element(move_input.at(0));
  char element2 = get_element(move_input.at(1));
  char element3 = get_element(move_input.at(2));

  if (element2 == '.') {
    cout << "*** Must jump a piece. Please retry.";
    return ok_move;
  }

  else if (element1 == '.') {
    cout << "*** Source needs a piece. Please retry.";
    return ok_move;
  }

  else if (element3 == '#') {
    cout << "*** Destination must be empty. Please retry.";
    return ok_move;
  }

  //checks if the move input is one of the valid options, starting at A and going through the whole board
  else if ((move_input.at(0) == 'A' && move_input.at(1) == 'B' && move_input.at(2) == 'E') || (move_input.at(0) == 'A' && move_input.at(1) == 'C' && move_input.at(2) == 'G') || (move_input.at(0) == 'A' && move_input.at(1) == 'D' && move_input.at(2) == 'I')) {
    ok_move = true;
  }
    
  else if ((move_input.at(0) == 'B' && move_input.at(1) == 'C' && move_input.at(2) == 'D') || (move_input.at(0) == 'B' && move_input.at(1) == 'G' && move_input.at(2) == 'L') || (move_input.at(0) == 'B' && move_input.at(1) == 'F' && move_input.at(2) == 'J')) {
    ok_move = true;
  }
    
  else if (move_input.at(0) == 'C' && move_input.at(1) == 'G' && move_input.at(2) == 'K') {
    ok_move = true;
  }
    
  else if ((move_input.at(0) == 'D' && move_input.at(1) == 'C' && move_input.at(2) == 'B') || (move_input.at(0) == 'D' && move_input.at(1) == 'G' && move_input.at(2) == 'J') || (move_input.at(0) == 'D' && move_input.at(1) == 'H' && move_input.at(2) == 'L')) {
    ok_move = true;
  }
    
  else if ((move_input.at(0) == 'E' && move_input.at(1) == 'B' && move_input.at(2) == 'A') || (move_input.at(0) == 'E' && move_input.at(1) == 'F' && move_input.at(2) == 'G') || (move_input.at(0) == 'E' && move_input.at(1) == 'J' && move_input.at(2) == 'M')) {
    ok_move = true;
  }
    
  else if (move_input.at(0) == 'F' && move_input.at(1) == 'G' && move_input.at(2) == 'H') {
    ok_move = true;
  }

  else if ((move_input.at(0) == 'G' && move_input.at(1) == 'C' && move_input.at(2) == 'A') || (move_input.at(0) == 'G' && move_input.at(1) == 'H' && move_input.at(2) == 'I') || (move_input.at(0) == 'G' && move_input.at(1) == 'K' && move_input.at(2) == 'M') || (move_input.at(0) == 'G' && move_input.at(1) == 'F' && move_input.at(2) == 'E')) {
    ok_move = true;
  }

  else if (move_input.at(0) == 'H' && move_input.at(1) == 'G' && move_input.at(2) == 'F') {
    ok_move = true;
  }

  else if ((move_input.at(0) == 'I' && move_input.at(1) == 'D' && move_input.at(2) == 'A') || (move_input.at(0) == 'I' && move_input.at(1) == 'H' && move_input.at(2) == 'G') || (move_input.at(0) == 'I' && move_input.at(1) == 'L' && move_input.at(2) == 'M')) {
    ok_move = true;
  }

  else if ((move_input.at(0) == 'J' && move_input.at(1) == 'F' && move_input.at(2) == 'B') || (move_input.at(0) == 'J' && move_input.at(1) == 'G' && move_input.at(2) == 'D') || (move_input.at(0) == 'J' && move_input.at(1) == 'K' && move_input.at(2) == 'L')) {
    ok_move = true;
  }

  else if (move_input.at(0) == 'K' && move_input.at(1) == 'G' && move_input.at(2) == 'C') {
    ok_move = true;
  }

  else if ((move_input.at(0) == 'L' && move_input.at(1) == 'H' && move_input.at(2) == 'D') || (move_input.at(0) == 'L' && move_input.at(1) == 'G' && move_input.at(2) == 'B') || (move_input.at(0) == 'L' && move_input.at(1) == 'K' && move_input.at(2) == 'J')) {
    ok_move = true;
  }

  else if ((move_input.at(0) == 'M' && move_input.at(1) == 'J' && move_input.at(2) == 'E') || (move_input.at(0) == 'M' && move_input.at(1) == 'K' && move_input.at(2) == 'G') || (move_input.at(0) == 'M' && move_input.at(1) == 'L' && move_input.at(2) == 'I')) {
    ok_move = true;
  }

  else {
    cout << "*** Move is invalid. Please retry.";
  }
  
  return ok_move;
}

void make_move(string move_input)
{
  /* TODO: Write a function that reads in a command from the user
  and  updates the  board, if  the  move  is valid.  ONLY use the
  functions get_element and set_element to update the board, do
  not access the array 'board' directly.
  */
  if (move_input == "R" || move_input == "r") {
      initialize_board();
    cout << "Restarting game.";
    return;
    }
  
  if (valid_move(move_input)) {
    set_element(move_input.at(0), '.');
    set_element(move_input.at(1), '.');
    set_element(move_input.at(2), '#');
  }
}