#include <iostream>
#include <string>
#include <list>

using namespace std;

// superclass for a general peice
class Peice {
    private:
        string name;
        bool colour; // 0 = white, 1 = green
        int row, col;

    public:
        string getName() {
            return name;
        }
        bool getColour() {
            return colour;
        }
        int getRow() {
            return row;
        }
        int getCol() {
            return col;
        }
        void setName(string n) {
            name = n;
        }
        void setColour(bool c) {
            colour = c;
        }
        void setRow(int r) {
            row = r;
        }
        void setCol(int c) {
            col = c;
        }
};


// pawn class
class Pawn: public Peice {
    public:
        Pawn(bool c) {
            setName("P");
            setColour(c);
        }
};

// rook class
class Rook: public Peice {
    public:
        Rook(bool c) {
            setName("R");
            setColour(c);
        }
};

// knight class
class Knight: public Peice {
    public:
        Knight(bool c) {
            setName("N");
            setColour(c);
        }
};

// bishop class
class Bishop: public Peice {
    public:
        Bishop(bool c) {
            setName("B");
            setColour(c);
        }
};

// queen class
class Queen: public Peice {
    public:
        Queen(bool c) {
            setName("Q");
            setColour(c);
        }
};

// king class
class King: public Peice {
    public:
        King(bool c) {
            setName("K");
            setColour(c);
        }
};

// chess game class
class Chess {
    private:
        Peice peices[8][8];

    public:
        Chess() {
            // pawns
            for (int i = 0; i < 8; i++) {
                Pawn greenPawn(1), whitePawn(0);
                peices[1][i] = greenPawn, peices[6][i] = whitePawn;
            }

            // rooks
            Rook greenRook1(1), greenRook2(1), whiteRook1(0), whiteRook2(0);
            peices[0][0] = greenRook1, peices[0][7] = greenRook2;
            peices[7][0] = whiteRook1, peices[7][7] = whiteRook2;

            // knights
            Knight greenKnight1(1), greenKnight2(1), whiteKnight1(0), whiteKnight2(0);
            peices[0][1] = greenKnight1, peices[0][6] = greenKnight2;
            peices[7][1] = whiteKnight1, peices[7][6] = whiteKnight2;

            // bishops
            Bishop greenBishop1(1), greenBishop2(1), whiteBishop1(0), whiteBishop2(0);
            peices[0][2] = greenBishop1, peices[0][5] = greenBishop2;
            peices[7][2] = whiteBishop1, peices[7][5] = whiteBishop2;

            // queens
            Queen greenQueen(1), whiteQueen(0);
            peices[0][3] = greenQueen, peices[7][4] = whiteQueen;

            // kings
            King greenKing(1), whiteKing(0);
            peices[0][4] = greenKing, peices[7][3] = whiteKing;

            nextTurn();
        }

        // display the board
        void printBoard() {
            cout << endl;
            for (int i = 0; i < 8; i++) {
                cout << "|-------------------------------|" << endl;
                cout << "| ";

                for (int j = 0; j < 8; j++) {
                    Peice peice = peices[i][j];
                    string end = " | ";

                    if (j == 7) {
                        int col = 7 - i;
                        end.append(1, char(56 - i));
                        end.append(1, '\n');
                    }
                    if (peice.getName() == "") {
                        cout << " " << end;
                    } else if (peice.getColour() == 1) { 
                        cout << "\033[32m" << peice.getName() << "\033[37m" << end;
                    } else {
                        cout << peice.getName() << end;
                    }
                }
            }
            cout << "|-------------------------------|" << endl;
            cout << "  a   b   c   d   e   f   g   h" << endl;
        }

        // starts the next move
        void nextTurn() {
            cout << endl << "White plays first." << endl;

            bool gameOver;
            bool currentTurn;
            do {
                printBoard();
                if (currentTurn == 0) {
                    gameOver = playerTurn("Player 1", 0);
                    currentTurn = 1;
                } else {
                    gameOver = playerTurn("Player 2", 1);
                    currentTurn = 0;
                }
            } while (gameOver == false);

            // ends the game
            printBoard();
            cout << endl << "Game over!" << endl;

            if (currentTurn == 1) {
                cout << endl << "Player 1 wins!" << endl << endl;
            } else {
                cout << endl << "Player 2 wins!" << endl << endl;
            }
        }

        // the user selects where to move
        bool playerTurn(string player, bool colour) {
            cout << endl << player << " select a peice to move:" << endl;
            string position;
            cin >> position;

            try {
                int row = 8 - stoi(position.substr(1, 2));
                int col = (int(position.substr(0, 1)[0]) - 97);

                if (row <= 7 && row >= 0 && col <= 7 && col >= 0) {
                    Peice peice = peices[row][col];
                    list<pair<int, int>> moves;
                    
                    if (peice.getName() != "") {
                        if (peice.getColour() == colour) {

                            // pawn moves
                            if (peice.getName() == "P") {
                                int direction;
                                if (peice.getColour() == 1) {
                                    direction = 1;
                                } else {
                                    direction = -1;
                                }

                                if (peices[row + direction][col].getName() == "") {
                                    moves.push_back({row + direction, col});

                                    if ((row = 1) && peice.getColour() == 1) {
                                        moves.push_back({row + 2, col});
                                    } else if ((row = 6) && peice.getColour() == 0) {
                                        moves.push_back({row - 2, col});
                                    }
                                }
                                if (peices[row + direction][col - 1].getName() != "") {
                                    if (col - 1 <= 7 && col - 1 >= 0) {
                                        moves.push_back({row + direction, col - 1});
                                    }
                                }
                                if (peices[row + direction][col + 1].getName() != "") {
                                    if (col + 1 <= 7 && col + 1 >= 0) {
                                        moves.push_back({row + direction, col + 1});
                                    }
                                }
                            }

                            // rook moves
                            if (peice.getName() == "R" || peice.getName() == "Q") {
                                for (int i = row + 1; i <= 7; i++) {
                                    if (peices[i][col].getName() == "") {
                                        moves.push_back({i, col});
                                    } else {
                                        if (peice.getColour() != peices[i][col].getColour()) {
                                            moves.push_back({i, col});
                                        }
                                        break;
                                    }
                                }
                                for (int i = row - 1; i >= 0; i--) {
                                    if (peices[i][col].getName() == "") {
                                        moves.push_back({i, col});
                                    } else {
                                        if (peice.getColour() != peices[i][col].getColour()) {
                                            moves.push_back({i, col});
                                        }
                                        break;
                                    }
                                }
                                for (int i = col + 1; i <= 7; i++) {
                                    if (peices[row][i].getName() == "") {
                                        moves.push_back({row, i});
                                    } else {
                                        if (peice.getColour() != peices[i][col].getColour()) {
                                            moves.push_back({row, i});
                                        }
                                        break;
                                    }
                                }
                                for (int i = col - 1; i >= 0; i--) {
                                    if (peices[row][i].getName() == "") {
                                        moves.push_back({row, i});
                                    } else {
                                        if (peice.getColour() != peices[i][col].getColour()) {
                                            moves.push_back({row, i});
                                        }
                                        break;
                                    }
                                }
                            }

                            // knight moves
                            if (peice.getName() == "N") {
                                list<pair<int, int>> knightMoves = {{row - 2, col - 1},
                                                                    {row - 2, col + 1},
                                                                    {row - 1, col + 2},
                                                                    {row + 1, col + 2},
                                                                    {row + 2, col + 1},
                                                                    {row + 2, col - 1},
                                                                    {row + 1, col - 2},
                                                                    {row - 1, col - 2}};

                                for (pair<int, int> knightMove : knightMoves) {
                                    if (knightMove.first <= 7 && knightMove.first >= 0 && knightMove.second <= 7 && knightMove.second >= 0) {
                                        if (peices[knightMove.first][knightMove.second].getName() == "") {
                                            moves.push_back({knightMove.first, knightMove.second});
                                        } else {
                                            if (peice.getColour() != peices[knightMove.first][knightMove.second].getColour()) {
                                                moves.push_back({knightMove.first, knightMove.second});
                                            }
                                        }
                                    }
                                }
                            }
                            
                            // bishop moves
                            if (peice.getName() == "B" || peice.getName() == "Q") {
                                bool blocks[4] = {true, true, true, true};

                                for (int i = 1; i <= 7; i++) {
                                    list<pair<int, int>> bishopMoves;

                                    if (blocks[0]) {
                                        bishopMoves.push_back({row - i, col - i});
                                    } else {
                                        bishopMoves.push_back({-1, -1});
                                    }
                                    if (blocks[1]) {
                                        bishopMoves.push_back({row - i, col + i});
                                    } else {
                                        bishopMoves.push_back({-1, -1});
                                    }
                                    if (blocks[2]) {
                                        bishopMoves.push_back({row + i, col + i});
                                    } else {
                                        bishopMoves.push_back({-1, -1});
                                    }
                                    if (blocks[3]) {
                                        bishopMoves.push_back({row + i, col - i});
                                    } else {
                                        bishopMoves.push_back({-1, -1});
                                    }

                                    int count = 0;
                                    for (pair<int, int> bishopMove : bishopMoves) {
                                        if (bishopMove.first <= 7 && bishopMove.first >= 0 && bishopMove.second <= 7 && bishopMove.second >= 0) {
                                            if (peices[bishopMove.first][bishopMove.second].getName() == "") {
                                                moves.push_back({bishopMove.first, bishopMove.second});
                                            } else {
                                                if (peice.getColour() != peices[bishopMove.first][bishopMove.second].getColour()) {
                                                    moves.push_back({bishopMove.first, bishopMove.second});
                                                }
                                                blocks[count] = false;
                                            }
                                        }
                                        ++count;
                                    }
                                }
                            }

                            // king moves
                            if (peice.getName() == "K") {
                                list<pair<int, int>> kingMoves = {{row - 1, col - 1},
                                                                  {row - 1, col},
                                                                  {row - 1, col + 1},
                                                                  {row, col + 1},
                                                                  {row + 1, col + 1},
                                                                  {row + 1, col},
                                                                  {row + 1, col - 1},
                                                                  {row, col - 1}};

                                for (pair<int, int> kingMove : kingMoves) {
                                    if (kingMove.first <= 7 && kingMove.first >= 0 && kingMove.second <= 7 && kingMove.second >= 0) {
                                        if (peices[kingMove.first][kingMove.second].getName() == "") {
                                            moves.push_back({kingMove.first, kingMove.second});
                                        } else {
                                            if (peice.getColour() != peices[kingMove.first][kingMove.second].getColour()) {
                                                moves.push_back({kingMove.first, kingMove.second});
                                            }
                                        }
                                    }
                                }                                    
                            }

                            // user selects possible move
                            if (moves.size() > 0) {
                                cout << endl << "Possible moves:" << endl;
                                int count = 1;
                                for (pair<int, int> move : moves) {
                                    cout << " " << count << ": " << char(move.second + 97) << (8 - move.first) << " ";
                                    ++count;
                                }

                                int index;
                                string indexString;
                                bool valid = false;
                                do {
                                    try {
                                        cout << endl << endl << player << " select a move:" << endl;
                                        cin >> indexString;
                                        index = stoi(indexString.substr(0, 1));

                                        if (index <= moves.size() && index > 0) {
                                            valid = true;
                                        }
                                    } catch(...) {
                                        valid = false;
                                    }
                                } while (valid == false);

                                // the move is made
                                list<pair<int, int>>::iterator it = moves.begin();
                                advance(it, index - 1);
                                pair<int, int> move = *it;

                                string last = peices[move.first][move.second].getName();
                                peices[move.first][move.second] = peice;
                                peices[row][col] = {};

                                if (last == "K") {
                                    return true;
                                }
                            } else {
                                throw("No moves available for that peice.");
                            }
                        } else {
                            throw("This peice does not belong to the player.");
                        }
                    } else {
                        throw("No peice is at this location.");
                    }
                } else {
                    throw("This is not a valid location.");
                }
            } catch (const char error[]) {
                cout << endl << "Error: " << error << endl;
                return playerTurn(player, colour);
            } catch (...) {
                cout << endl << "This is not a valid string." << endl;
                return playerTurn(player, colour);
            }
            return false;
        }
};

// main
int main() {
    Chess chess;
    return 0;
}