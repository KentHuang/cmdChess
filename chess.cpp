#include <iostream>
#include <regex>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::string;
using std::vector;

void printBoard(string* tiles) {
  string delm = "|---|---|---|---|---|---|---|---|";

  cout << delm << endl;
  int i = 0;
  do {
  	cout << "|" << tiles[i];
  	++i;
  	if (i%8 == 0) { cout << "|" << endl << delm << endl; }
  } while (i < 64);
}

void boardInit(string* tiles) {

  tiles[0] = tiles[7] = "-R ";
  tiles[1] = tiles[6] = "-N ";
  tiles[2] = tiles[5] = "-B ";
  tiles[3] = "-Q ";
  tiles[4] = "-K ";

  tiles[56] = tiles[63] = "+R ";
  tiles[57] = tiles[62] = "+N ";
  tiles[58] = tiles[61] = "+B ";
  tiles[59] = "+Q ";
  tiles[60] = "+K ";

  for (int i = 8; i < 16; ++i) { tiles[i] = "-P "; }
  for (int i = 48; i < 56; ++i) { tiles[i] = "+P "; }
  for (int i = 16; i < 48; ++i) { tiles[i] = "   "; }
}

// ie. (R, e8, f2, x, #)
void parseInput(string input, string& piece, string& fromPos, string& toPos, char& op, char& postOp) {
  regex e("[RNBQK]");
  bool m = regex_match(input.begin(), input.begin()+1, e);
  if (m) { 
    piece = input[0]; 
    input = input.substr(1, input.size()-1); 
  } else { piece = "P"; }

  fromPos = input.substr(0, 2);
  op = input[2];
  toPos = input.substr(3,2);

  if (input.size() > 5) { 
    postOp = input[5];
  }
}

// example: "a8" -> 0, "b8" -> 1
int coordToIndex(string coord) {
  int col;
  switch (coord[0]) {
    case 'a': col = 0; break;
    case 'b': col = 1; break;
    case 'c': col = 2; break;
    case 'd': col = 3; break;
    case 'e': col = 4; break;
    case 'f': col = 5; break;
    case 'g': col = 6; break;
    case 'h': col = 7; break;
    default: cout << "error in coordinates" << endl;
  }
  return (8 - ((int)coord[1] - 48)) * 8 + col;
}


int main() {
  
  string board[64];
  boardInit(board);
  const regex validNotes("[RNBQK]*[a-h][1-8][x-]+[a-h][1-8][+#]*");
  char turn = '+';
  vector<string> moves;
  
  while (true) {
  	string input;
    string piece;
    string from;
    string to;
    char op;
    char postOp;
    bool regMatched;
    bool validPiece;
    bool validPlayerPiece;
    bool validMove;
    string error("");

  	do {
  	  printBoard(board);
  	  cout << error << ((turn == '+') ? "White, " : "Black, ") << "make your move: ";
  	  cin >> input;
  	  regMatched = regex_match(input, validNotes);

      if (regMatched) {
        parseInput(input, piece, from, to, op, postOp);
      } else {
        error = "Invalid input syntax. ";
        continue;
      }

      validPiece = board[coordToIndex(from)].compare(piece);
      if (!validPiece) { error = "Invalid piece type. "; }

      validPlayerPiece = (turn == board[coordToIndex(from)][0]) ? true : false;
      if (validPlayerPiece) { error = "Invalid piece color. "; }

  	} while (!regMatched || !validPiece || !validPlayerPiece || !validMove);

    std::swap(board[coordToIndex(from)], board[coordToIndex(to)]);
  	moves.push_back(input);
  	if (turn == '+') {
      turn = '-';
    } else {
      turn = '+';
    }    
  }

  return 0;
}
