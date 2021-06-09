#include <iostream>
#include <string>
#include <tuple>
#include <cmath>
#include <list>

using namespace std;

// superclass for a general peice
class Peice {
    private:
        string name;
        bool colour; // 0 = white, 1 = green
        int row, col, weight;

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
        int getWeight() {
            return weight;
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
        void setWeight(int w) {
            weight = w;
        }
};


// pawn class
class Pawn: public Peice {
    public:
        Pawn(bool c) {
            setName("P");
            setColour(c);
            setWeight(1);
        }
};

// rook class
class Rook: public Peice {
    public:
        Rook(bool c) {
            setName("R");
            setColour(c);
            setWeight(5);
        }
};

// knight class
class Knight: public Peice {
    public:
        Knight(bool c) {
            setName("N");
            setColour(c);
            setWeight(3);
        }
};

// bishop class
class Bishop: public Peice {
    public:
        Bishop(bool c) {
            setName("B");
            setColour(c);
            setWeight(4);
        }
};

// queen class
class Queen: public Peice {
    public:
        Queen(bool c) {
            setName("Q");
            setColour(c);
            setWeight(9);
        }
};

// king class
class King: public Peice {
    public:
        King(bool c) {
            setName("K");
            setColour(c);
            setWeight(0);
        }
};

// chess game class
class Chess {
    private:
        Peice peices[8][8];

    public:
        Chess() {
            // pawns
            for (int i = 0; i <= 7; i++) {
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
            for (int i = 0; i <= 7; i++) {
                cout << "|-------------------------------|" << endl;
                cout << "| ";

                for (int j = 0; j <= 7; j++) {
                    Peice peice = peices[i][j];
                    string end = " | ";

                    if (j == 7) {
                        end.append(1, char(56 - i));
                        end.append(1, '\n');
                    }
                    if (peice.getName() != "") {
                        if (peice.getColour() == 1) { 
                            cout << "\033[32m" << peice.getName() << "\033[37m" << end;
                        } else {
                            cout << peice.getName() << end;
                        }
                    } else {
                        cout << " " << end;
                    }
                }
            }
            cout << "|-------------------------------|" << endl;
            cout << "  a   b   c   d   e   f   g   h" << endl;
        }

        // starts the next move
        void nextTurn() {
            cout << endl << "White plays first." << endl;

            bool gameOver = 0, currentTurn = 1;
            do {
                if (currentTurn == 1) {
                    printBoard();
                    gameOver = playerTurn();
                    currentTurn = 0;
                } else {
                    gameOver = aiTurn();
                    currentTurn = 1;
                }
            } while (gameOver == 0);

            // ends the game
            if (currentTurn == 0) {
                printBoard();
                cout << endl << "Game over!" << endl << endl << "Player 1 wins!" << endl << endl;
            } else {
                cout << endl << "Game over!" << endl << endl << "AI wins!" << endl << endl;
            }
        }

        // the user selects where to move
        bool playerTurn() {
            cout << endl << "Player, select a peice to move:" << endl;
            string position;
            cin >> position;

            try {
                int row = 8 - stoi(position.substr(1, 2));
                int col = (int(position.substr(0, 1)[0]) - 97);

                if (row <= 7 && row >= 0 && col <= 7 && col >= 0) {
                    Peice peice = peices[row][col];
                    
                    if (peice.getName() != "") {
                        if (peice.getColour() == 0) {
                            list<pair<int, int>> moves = getMoves(peice.getName(), 0, row, col);

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
                                bool valid = 0;
                                do {
                                    try {
                                        cout << endl << endl << "Player, select a move:" << endl;
                                        cin >> indexString;
                                        index = stoi(indexString.substr(0, 1));

                                        if (index <= (int) moves.size() && index > 0) {
                                            valid = 1;
                                        }
                                    } catch(...) {
                                        valid = 0;
                                    }
                                } while (valid == 0);

                                list<pair<int, int>>::iterator it = moves.begin();
                                advance(it, index - 1);
                                return makeMove(*it, row, col);
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
                return playerTurn();
            } catch (...) {
                cout << endl << "This is not a valid string." << endl;
                return playerTurn();
            }
            return 0;
        }

        // the "AI" makes a move
        bool aiTurn() {
            list<tuple<int, int, int, pair<int, int>>> blackPeices;

            for (int i = 0; i <= 7; i++) {
                for (int j = 0; j <= 7; j++) {
                    if (peices[i][j].getName() != "" && peices[i][j].getColour() == 1) {
                        list<pair<int, int>> moves = getMoves(peices[i][j].getName(), 1, i, j);
                        if (moves.size() > 0){
                            int maxWeight;
                            pair<int, int> maxMove = moves.front();
                            for (pair<int, int> move : moves) {
                                int weight = (peices[move.first][move.second].getWeight()) + i;
                                if (weight > maxWeight) {
                                    maxWeight = weight;
                                    maxMove = move;
                                }
                            }
                            blackPeices.push_back({i, j, (5 * (i + 1)) + (10 * maxWeight) + (4 - (round (abs (3.5 - j)))) + (2 * peices[i][j].getWeight()), maxMove});
                        }
                    }
                }
            }
            blackPeices.sort([] (const tuple<int, int, int, pair<int, int>> & a, const  tuple<int, int, int, pair<int, int>> & b) {
                return (get<2>(a) > get<2>(b));
            });
            for (tuple<int, int, int, pair<int, int>> blackPeice : blackPeices) {
                return makeMove({get<3>(blackPeice).first, get<3>(blackPeice).second}, get<0>(blackPeice), get<1>(blackPeice));
            }
        }

        // gets the moves for an unknown peice
        list<pair<int, int>> getMoves(string name, bool colour, int row, int col) {
            list<pair<int, int>> moves;
            if (name == "P") {
                moves = getPawnMoves(colour, row, col);
            } else if (name == "R") {
                moves = getRookMoves(colour, row, col);
            } else if (name == "N") {
                moves = getKnightMoves(colour, row, col);
            } else if (name == "B") {
                moves = getBishopMoves(colour, row, col);
            } else if (name == "Q") {
                moves = getRookMoves(colour, row, col);
                moves.merge(getBishopMoves(colour, row, col));
            } else if (name == "K") {
                moves = getKingMoves(colour, row, col);                                    
            }
            return moves;
        }

        // the move is made
        bool makeMove(pair<int, int> move, int row, int col) {
            string last = peices[move.first][move.second].getName();
            peices[move.first][move.second] = peices[row][col];
            peices[row][col] = {};

            if (last == "K") {
                return 1;
            } else {
                // check for a check or checkmate
                list<pair<int, int>> kingMoves, peiceMoves;
                int count;

                // get king moves
                for (int i = 0; i <= 7; i++) {
                    for (int j = 0; j <= 7; j++) {
                        if (peices[i][j].getName() == "K") {
                            if (peices[i][j].getColour() == 0) {
                                kingMoves = getKingMoves(0, i, j);
                                break;
                            }
                        }
                    }
                }

                // get all the response moves
                for (int i = 0; i <= 7; i++) {
                    for (int j = 0; j <= 7; j++) {
                        if (peices[i][j].getName() != "" && peices[i][j].getColour() == 1) {
                            peiceMoves = getMoves(peices[i][j].getName(), 1, i, j);
                        }
                    }
                }
                peiceMoves.sort();
                peiceMoves.unique();

                // check if check or checkmate
                for (pair<int, int> peiceMove : peiceMoves) {
                    for (pair<int, int> kingMove : kingMoves) {
                        if (peiceMove.first == kingMove.first && peiceMove.second == kingMove.second) {
                            cout << peiceMove.first << peiceMove.second << " ";
                            ++count;
                        }
                    }
                }
                if (count == (int) kingMoves.size() && count > 0) {
                    cout << endl << "Checkmate!" << endl;
                    return 1;
                } else if (count > 0) {
                    cout << endl << "Check!" << endl;
                }
            }
            return 0;
        }

        // pawn moves
        list<pair<int, int>> getPawnMoves(bool colour, int row, int col) {
            list<pair<int, int>> moves;
            int direction;

            if (colour == 1) {
                direction = 1;
            } else {
                direction = -1;
            }

            if (peices[row + direction][col].getName() == "") {
                moves.push_back({row + direction, col});

                if (row == 1 && colour == 1) {
                    moves.push_back({row + 2, col});
                } else if (row == 6 && colour == 0) {
                    moves.push_back({row - 2, col});
                }
            }
            if (peices[row + direction][col - 1].getName() != "") {
                if (col - 1 <= 7 && col - 1 >= 0) {
                    if (colour != peices[row + direction][col - 1].getColour()) {
                        moves.push_back({row + direction, col - 1});
                    }
                }
            }
            if (peices[row + direction][col + 1].getName() != "") {
                if (col + 1 <= 7 && col + 1 >= 0) {
                    if (colour != peices[row + direction][col + 1].getColour()) {
                        moves.push_back({row + direction, col + 1});
                    }
                }
            }
            return moves;
        }

        // rook moves
        list<pair<int, int>> getRookMoves(bool colour, int row, int col) {
            list<pair<int, int>> moves;

            for (int i = row + 1; i <= 7; i++) {
                if (peices[i][col].getName() == "") {
                    moves.push_back({i, col});
                } else {
                    if (colour != peices[i][col].getColour()) {
                        moves.push_back({i, col});
                    }
                    break;
                }
            }
            for (int i = row - 1; i >= 0; i--) {
                if (peices[i][col].getName() == "") {
                    moves.push_back({i, col});
                } else {
                    if (colour != peices[i][col].getColour()) {
                        moves.push_back({i, col});
                    }
                    break;
                }
            }
            for (int i = col + 1; i <= 7; i++) {
                if (peices[row][i].getName() == "") {
                    moves.push_back({row, i});
                } else {
                    if (colour != peices[row][i].getColour()) {
                        moves.push_back({row, i});
                    }
                    break;
                }
            }
            for (int i = col - 1; i >= 0; i--) {
                if (peices[row][i].getName() == "") {
                    moves.push_back({row, i});
                } else {
                    if (colour != peices[row][i].getColour()) {
                        moves.push_back({row, i});
                    }
                    break;
                }
            }
            return moves;
        }
        
        // knight moves
        list<pair<int, int>> getKnightMoves(bool colour, int row, int col) {
            list<pair<int, int>> moves;
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
                        if (colour != peices[knightMove.first][knightMove.second].getColour()) {
                            moves.push_back({knightMove.first, knightMove.second});
                        }
                    }
                }
            }
            return moves;
        }

        // bishop moves
        list<pair<int, int>> getBishopMoves(bool colour, int row, int col) {
            list<pair<int, int>> moves;
            bool blocks[4] = {1, 1, 1, 1};

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
                            if (colour != peices[bishopMove.first][bishopMove.second].getColour()) {
                                moves.push_back({bishopMove.first, bishopMove.second});
                            }
                            blocks[count] = 0;
                        }
                    }
                    ++count;
                }
            }
            return moves;
        }

        // king moves
        list<pair<int, int>> getKingMoves(bool colour, int row, int col) {
            list<pair<int, int>> moves;
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
                        if (colour != peices[kingMove.first][kingMove.second].getColour()) {
                            moves.push_back({kingMove.first, kingMove.second});
                        }
                    }
                }
            }
            return moves;            
        }
};

// main
int main() {
    Chess chess;
    return 0;
}