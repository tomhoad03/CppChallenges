#include <iostream>
#include <windows.h>

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
            setName("R");
            setColour(c);
        }
};

// queen class
class Queen: public Peice {
    public:
        Queen(bool c) {
            setName("R");
            setColour(c);
        }
};

// king class
class King: public Peice {
    public:
        King(bool c) {
            setName("R");
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
            peices[0][3] = greenQueen, peices[7][3] = whiteQueen;

            // kings
            King greenKing(1), whiteKing(0);
            peices[0][4] = greenKing, peices[7][4] = whiteKing;
        }

        // display the board
        void printBoard() {
            for (int i = 0; i < 8; i++) {
                cout << "|-------------------------------|" << endl;
                cout << "| ";

                for (int j = 0; j < 8; j++) {
                    Peice peice = peices[i][j];
                    string end = " | ";

                    if (j == 7) {
                        end = " |\n";
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
        }
};

int main() {
    Chess chess;
    chess.printBoard();

    return 0;
}