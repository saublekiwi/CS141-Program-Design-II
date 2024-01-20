#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;


class Scrambler {
  public:
    Scrambler(const string&, const int);

    string str() const;
    void try_move(const string&);
    bool is_over() const;
    string display_solution() const;
    vector<string> get_words() const;

  private:
    int board_size;
    string solution;

    vector <vector<string>> board;
    vector <vector<string>> board_solved;
    vector <vector<string>> board_jumbled;


    vector <string> dictionary_vector;
    vector <string> words_on_board;
    vector <string> moves_by_scramble;
    vector <string> moves_by_scramble_inverse;

    void populate_board();
    void jumble_board();
    void make_solution();
};



Scrambler::Scrambler (const string& path, const int size) {
  board_size = size;
  
  string word;

  ifstream dictionary{path};

  while (dictionary.eof() != true) { //Loops through each line and adds the word to dictionary_vector
    getline(dictionary, word);
    dictionary_vector.push_back(word);
  }
  
  dictionary.close();
  
  board.resize(board_size); //Sets the board size
  for (int row = 0; row < board_size; row++) {
    board.at(row).resize(board_size);
  }

  for (int i = 0; i < size; i++) { //Fills the board with spaces
    for (int j = 0; j < size; j++) {
      board.at(i).at(j) = ' ';
    }
  }

  populate_board();

  board_solved = board; //Makes a copy of the solved board before it's jumbled

  jumble_board();

  board_jumbled = board; //Makes a copy of the original jumbled board (the starting board for the player)

  make_solution();
}


void Scrambler::populate_board() {
  int current_pos = 0, word_index = 0, space_needed;
  int dictionary_size = dictionary_vector.size();
  string word;
  bool not_first;
  
  
  for (int row = 0; row < board_size; row++) { //Adds words to the board
    not_first = true;
    space_needed = 3;
    current_pos = 0;
    
    while (current_pos <= board_size - space_needed) {
      word_index = rand() % dictionary_size; //Random index in dictionary
      word = dictionary_vector.at(word_index); //Word at index

      if (word.size() <= board_size - current_pos - (space_needed - 3) && board_size - current_pos > space_needed - 1) {

        words_on_board.push_back(word);
        
        if (!not_first) {
          current_pos++;
        }

        not_first = false;
        space_needed = 4;
        
        for (char l: word) {
          board.at(row).at(current_pos) = l;
          current_pos++;
        }
      }
    }
  }
}

void Scrambler::jumble_board() { //creates the random moves to scamble the board and trys them
  int x = rand() % 8, nmoves = x + 3, idx, letter_decider;
  char row_or_col, dir;

  for (int i = 0; i < nmoves; i++) {
    idx = rand() % board_size;
    letter_decider = rand();

    if (i % 2 == 0) {
      row_or_col = 'c';
      
      if (letter_decider % 2 == 0) {
        dir = 'u';
      }

      else {
        dir = 'd';
      }
    }

    else {
      row_or_col = 'r';
      
      if (letter_decider % 2 == 0) {
        dir = 'l';
      }

      else {
        dir = 'r';
      }
    }

    moves_by_scramble.push_back(row_or_col + to_string(idx+1) + dir); //keeps track of the moves made

    try_move(row_or_col + to_string(idx+1) + dir);
  }
}

string Scrambler::str() const {
  string board_string, add_on_string;

  board_string = " "; //first line
  for (int i = 1; i <= board_size; i++) {
    board_string += "   " + to_string(i);
  }
  board_string += "\n";

  board_string += "   "; //second line
  for (int i = 0; i < board_size; i++) {
    board_string += "----";
  }
  board_string += "\n";

  for (int row = 0; row < board_size; row++) { //rest of the lines
    board_string += to_string(row + 1);
    
    for (int col = 0; col < board_size; col++){
      board_string += " | " + board.at(row).at(col);
    }
    
    board_string += " |\n";

    board_string += "   "; //Horizontal lines
  for (int i = 0; i < board_size; i++) {
    board_string += "----";
  }
  board_string += "\n";
  }

  board_string.pop_back(); //removes the last newline
  
  return board_string;
}

void Scrambler::try_move(const string& cmd) {
  string lower_cmd, temp;
  
  for (char c : cmd) { //Makes cmd all lowercase
    c = tolower(c);
    lower_cmd.push_back(c);
  }

  if (lower_cmd.at(0) == 'r' && lower_cmd.size() == 1) { //Checks if the board should be reset
    board = board_jumbled;
    return;
  }

  lower_cmd.at(1) = cmd.at(1) - 49;
  
  if (lower_cmd.at(1) >= 0 && lower_cmd.at(1) < board_size) { //makes sure the row/col input is on the board
    if (lower_cmd.at(0) == 'c') { //selects column
      if (lower_cmd.at(2) == 'u') { //move up
        temp = board.at(0).at(lower_cmd.at(1)); //top of column
        
        for (int i = 0; i < board_size - 1; i++) {
          board.at(i).at(lower_cmd.at(1)) = board.at(i + 1).at(lower_cmd.at(1));
        }
        board.at(board_size - 1).at(lower_cmd.at(1)) = temp;
      }
    
      else if (lower_cmd.at(2) == 'd') { //move down
        temp = board.at(board_size - 1).at(lower_cmd.at(1)); //bottom of column
        
        for (int i = board_size - 1; i > 0; i--) {
          board.at(i).at(lower_cmd.at(1)) = board.at(i - 1).at(lower_cmd.at(1));
        }
        board.at(0).at(lower_cmd.at(1)) = temp;
      }
    }
    
    else if (lower_cmd.at(0) == 'r') { //selects row
      if (lower_cmd.at(2) == 'l') { //move left
        temp = board.at(lower_cmd.at(1)).at(0); //left most of row

        for (int i = 0; i < board_size - 1; i++) {
          board.at(lower_cmd.at(1)).at(i) = board.at(lower_cmd.at(1)).at(i + 1);
        }
        board.at(lower_cmd.at(1)).at(board_size - 1) = temp;
      }
    
      else if (lower_cmd.at(2) == 'r') { //move right
        temp = board.at(lower_cmd.at(1)).at(board_size - 1); //right most of row

        for (int i = board_size - 1; i > 0; i--) {
          board.at(lower_cmd.at(1)).at(i) = board.at(lower_cmd.at(1)).at(i - 1);
        }
        board.at(lower_cmd.at(1)).at(0) = temp;
      }
    }
  }
}

bool Scrambler::is_over() const { //checks each group of horizontal slots that are word length to see if it is the word
  int num_words = words_on_board.size(), num_found = 0, word_length;
  string word, word_to_check;

  for (int i = 0; i < num_words; i++) {
    word = words_on_board.at(i);
    word_length = word.size();
    word_to_check = "";

    for (int row = 0; row < board_size; row++) {
      for (int col = 0; col < board_size - word_length + 1; col++) {
        word_to_check = "";
        
        for (int start = col; start < col + word_length; start++) {
          word_to_check += board.at(row).at(start);
        }

        if (word_to_check == word) {
          num_found++;
        }
      }
    }
  }
  
  if (num_found == num_words) {
    return true;
  }

  else {
    return false;
  }
}

void Scrambler::make_solution() { //makes the solution by inverting the moves made by the scrambler, making those moves and adding it all to a string, finally resetting the board state to being scrambled
  int num_moves = moves_by_scramble.size();
  string inverse_move;

  for (int move = num_moves - 1; move >= 0; move--) {
    inverse_move = moves_by_scramble.at(move);
    
    if (inverse_move.at(2) == 'u') {
      inverse_move.pop_back();
      inverse_move.push_back('d');
    }
  
    else if (inverse_move.at(2) == 'd') {
      inverse_move.pop_back();
      inverse_move.push_back('u');
    }

    else if (inverse_move.at(2) == 'l') {
      inverse_move.pop_back();
      inverse_move.push_back('r');
    }

    else {
      inverse_move.pop_back();
      inverse_move.push_back('l');
    }

    moves_by_scramble_inverse.push_back(inverse_move);
  }

  solution += str();
  
  for (int move = 0; move < num_moves; move++) {
    solution += "\n*** Move " + to_string(move + 1) + " (" + moves_by_scramble_inverse.at(move).at(0) + "," + moves_by_scramble_inverse.at(move).at(1) + "," + moves_by_scramble_inverse.at(move).at(2) + ")\n";

    try_move(moves_by_scramble_inverse.at(move));

    solution += str();
  }

  board = board_jumbled;
}

string Scrambler::display_solution() const {
  return solution;
}

vector<string> Scrambler::get_words() const {
  return words_on_board;
}



int main() {
  srand(time(NULL));
  Scrambler huh("dictionary.txt", 8);
  cout << huh.display_solution();
  return 0;
}