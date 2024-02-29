#include <iostream>
#include <vector>
using namespace std;
int rows = 6;
int cols = 7;
char empty_cell = '#';

// initializing the board with empty_cell to visualize the breadth of the board by using #.
vector<vector<char> > initializeBoard() {
    return vector<vector<char> >(rows, vector<char>(cols, empty_cell));
}
// print the board.
void print_board(const vector<vector<char> >& board) {
    for (int i = rows - 1; i >= 0; i--) {
        // The output is put here in the outer loop to make the index column before each row.
        cout <<i+1<< " ";
        for (int j = 0; j < cols; j++) {
            
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    // The index row doesn't need a loop.
    cout << "  1 2 3 4 5 6 7" << endl;
}

// function to check whether the player's move is valid, using bool data type that has either true or false values.
bool valid_move(const vector<vector<char> >& board, int column) {
    return column >= 1 && column <= cols && board[rows - 1][column - 1] == empty_cell;
}

// function to drop a player's coin into the board.
void dropcoin(vector<vector<char> >& board, int column, char coin) {
    for (int i = 0; i < rows; i++) {
        if (board[i][column - 1] == empty_cell) {
            board[i][column - 1] = coin;
            break;
        }
    }
}

// checking satisfied win conditions.
bool checkWin(const vector<vector<char> >& board, char coin) {
    //horizontal
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= cols - 4; j++) {
            if (board[i][j] == coin && board[i][j + 1] == coin && 
                board[i][j + 2] == coin && board[i][j + 3] == coin) {
                return true;
            }
        }
    }
    //vertical
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == coin && board[i + 1][j] == coin && 
                board[i + 2][j] == coin && board[i + 3][j] == coin) {
                return true;
            }
        }
    }
    //positive diagonals
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= cols - 4; j++) {
            if (board[i][j] == coin && board[i + 1][j + 1] == coin && 
                board[i + 2][j + 2] == coin && board[i + 3][j + 3] == coin) {
                return true;
            }
        }
    }
    //negative diagonals 
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < cols; j++) {
            if (board[i][j] == coin && board[i + 1][j - 1] == coin && 
                board[i + 2][j - 2] == coin && board[i + 3][j - 3] == coin) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<vector<char> > board = initializeBoard();
    bool gameover = false;
    int turn = 1;
    char coin;
    while (!gameover) {
        print_board(board);
        if (turn%2!=0){
            coin = 'X';
        }else{
            coin = 'O';
        }
        //a player enters a move by selecting the column to drop into.
        int column;
        cout << "Player " << coin << ", enter column (1-7): ";
        cin >> column;

        if (!valid_move(board, column)) {
            cout << "Invalid move. Please enter a valid move." << endl;
            continue;
        }

        //drop coin into the board
        dropcoin(board, column, coin);

        //check winning conditions.
        if (checkWin(board, coin)) {
            print_board(board);
            cout << "Player " << coin << " wins" << endl;
            gameover = true;
        }

        // If there is no winner, then check draw
        bool isDraw = true;
        for (int i = 0; i < cols; i++) {
            if (valid_move(board, i + 1)) {
                isDraw = false;
                break;
            }
        }
        if (isDraw) {
            print_board(board);
            cout << "A draw" << endl;
            gameover = true;
        }

        //increment turns variable to change the type of coin to allow the second player to make a move
        turn++;
    }

    return 0;
}