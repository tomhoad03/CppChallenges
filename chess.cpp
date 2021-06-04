#include <iostream>

using namespace std;

class Peice {
    private:
        string name;
        bool colour; // 0 = white, 1 = black
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

class Pawn: public Peice {
    public:
        Pawn(bool c) {
            setName("P");
            setColour(c);
        }
};

class Chess {
    private:
        Peice peices[8][8];

    public:
        Chess() {
            for (int i = 0; i < 8; i++) {
                Pawn blackPawn(1), whitePawn(0);
                peices[1][i] = blackPawn;
                peices[6][i] = whitePawn;
            }
        }

        void printBoard() {
            for (int i = 0; i < 8; i++) {
                cout << "|-------------------------------|" << endl;
                cout << "| ";

                for (int j = 0; j < 7; j++) {
                    string peice = peices[i][j].getName();
                    if (peice.length() == 0) {
                        peice = " ";
                    }
                    cout << peice << " | ";
                }
                string peice = peices[i][7].getName();
                if (peice.length() == 0) {
                    peice = " ";
                }
                cout << peice << " |" << endl;
            }
            cout << "|-------------------------------|" << endl;
        }
};

int main() {
    Chess chess;
    chess.printBoard();

    return 0;
}