#include <iostream>
using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char currentMarker;
int currentPlayer;
void drawBoard() {
    cout << "\n " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    }
    return false;
}
int winner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return currentPlayer;
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return currentPlayer;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return currentPlayer;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return currentPlayer;

    return 0; 
}
void game() {
    cout << "\nPlayer 1, choose your marker (X or O): ";
    cin >> currentMarker;
    if (currentMarker == 'x') currentMarker = 'X';
    if (currentMarker == 'o') currentMarker = 'O';
    if (currentMarker != 'X' && currentMarker != 'O') {
        cout << "Invalid input! Defaulting marker to 'X'.\n";
        currentMarker = 'X';
    }

    currentPlayer = 1;
    drawBoard();
    int playerWon = 0;
    for (int i = 0; i < 9; i++) {
        int slot;
        cout << "\nPlayer " << currentPlayer << "'s turn (" << currentMarker << "). Enter slot (1-9): ";
        cin >> slot;
        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid move! Try another slot.\n";
            i--; 
            continue;
        }
        drawBoard();
        playerWon = winner();
        if (playerWon != 0) {
            cout << "\n=======================================" << endl;
            cout << "Congratulations! Player " << playerWon << " wins!" << endl;
            cout << "=======================================" << endl;
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        currentMarker = (currentMarker == 'X') ? 'O' : 'X';
    }
    if (playerWon == 0) {
        cout << "\nIt's a draw game!\n";
    }
}
int main() {
    char choice;
    do {
        char start = '1';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) board[i][j] = start++;
        }
        cout << "=======================================" << endl;
        cout << "          TIC-TAC-TOE GAME             " << endl;
        cout << "=======================================" << endl;
        game();
        cout << "\nDo you want to play another game? (y/n): ";
        cin >> choice;
        cout << endl;
    } while (choice == 'y' || choice == 'Y');
    cout << "Thank you for playing!" << endl;
    return 0;
}