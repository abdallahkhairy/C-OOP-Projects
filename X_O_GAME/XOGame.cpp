#include "XOGame.h"

XOGame::XOGame() : matrix{ {' ',' ',' '}, {' ',' ',' '} , {' ',' ',' '} },
                   player1_name("Player 1"), player2_name("Player 2"), player_turn("Player 1"),
                   end_flag(0), row(0), col(0), match_number(1) {
    cout << "              ***********************" << endl;
    cout << "              *                     *" << endl;
    cout << "              * Welcome To X O Game *" << endl;
    cout << "              *                     *" << endl;
    cout << "              ***********************" << endl;
}

void XOGame::displayMatrix() {
    cout << endl << "Matrix : " << endl << endl;
    for (int i = 0; i < MATRIX_ROWS; i++)
    {
        for (int j = 0; j < MATRIX_COLS; j++)
        {
            cout << " [ " << matrix[i][j] << " ] ";
        }
        cout << endl << endl;
    }
}

void XOGame::setPlayersNames() {
    cout << endl << "Enter First Player Name : ";
    getline(cin, player1_name);
    cout << endl << "Enter Second Player Name : ";
    getline(cin, player2_name);
}

void XOGame::displayScore() {
    cout << endl << endl << "Match Number : " << match_number++ << endl << endl;
    cout << "Score : " << setw(15) << left << player1_name << " = " << player1_score << endl;
    cout << "        " << setw(15) << left << player2_name << " = " << player2_score << endl;
}

void XOGame::play() {
    if (0 == player_flag) {
        cout << endl << player1_name << ", Choose The Position ( Enter RAW then press space then COLUMN ) : " << endl;
        cin >> row >> col;
        row--, col--;
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || matrix[row][col] != ' ') {
            cout << endl << "Invalid Indices Please Enter Indices between 1 - 3 " << endl;
            return;
        }

        matrix[row][col] = 'X';
        player_flag = 1;
    }
    else if (1 == player_flag) {
        cout << endl << player2_name << ", Choose The Position ( Enter RAW then press space then COLUMN ) : " << endl;
        cin >> row >> col;
        row--, col--;
        if ((row < 0) || (row >= 3) || (col < 0) || (col >= 3)) {
            cout << endl << "Invalid Indices, Please Enter Indices between 1 - 3 " << endl;
            return;
        }
        else if (matrix[row][col] != ' ') {
            cout << endl << "This Position Isn`t Empty, Please Choose Empty Position " << endl;
            return;
        }
        else {
            matrix[row][col] = 'Y';
            player_flag = 0;
        }
    }
    else { /* Nothing */ }

    displayMatrix();

    // Check rows, columns for a match
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        if ((matrix[i][0] != ' ') && (matrix[i][0] == matrix[i][1]) && (matrix[i][1] == matrix[i][2])) {
            if (0 == i) {
                cout << endl << "First Row Matched ---" << endl;
            }
            else if (1 == i) {
                cout << endl << "First Row Matched ---" << endl;
            }
            else if (2 == i) {
                cout << endl << "Third Row Matched ---" << endl;
            }
            else { /* Nothing */ }


            if (1 == player_flag) {
                cout << "[ " << player1_name << " ] Has Won !!!!!!!" << endl;
                player1_score++;
                player_flag = 0;
            }
            else if (0 == player_flag) {
                cout << "[ " << player2_name << " ] Has Won !!!!!!!" << endl;
                player2_score++;
                player_flag = 1;
            }
            else { /* Nothing */ }
            end_flag = 1;
        }
        if ((matrix[0][i] != ' ') && (matrix[0][i] == matrix[1][i]) && (matrix[1][i] == matrix[2][i])) {
            if (0 == i) {
                cout << endl << "First Column Matched |" << endl;
            }
            else if (1 == i) {
                cout << endl << "First Column Matched |" << endl;
            }
            else if (2 == i) {
                cout << endl << "Third Column Matched |" << endl;
            }
            else { /* Nothing */ }

            if (1 == player_flag) {
                cout << "[ " << player1_name << " ] Has Won !!!!!!!" << endl;
                player1_score++;
                player_flag = 0;
            }
            else if (0 == player_flag) {
                cout << "[ " << player2_name << " ] Has Won !!!!!!!" << endl;
                player2_score++;
                player_flag = 1;
            }
            else { /* Nothing */ }
            end_flag = 1;
        }
    }
    // Check diagonals for a match
    if ((matrix[0][0] != ' ') && (matrix[0][0] == matrix[1][1]) && (matrix[1][1] == matrix[2][2])) {
        cout << endl << "Left Diagonal Matched \\" << endl;
        if (1 == player_flag) {
            cout << "[ " << player1_name << " ] Has Won !!!!!!!" << endl;
            player1_score++;
            player_flag = 0;
        }
        else if (0 == player_flag) {
            cout << "[ " << player2_name << " ] Has Won !!!!!!!" << endl;
            player2_score++;
            player_flag = 1;
        }
        else { /* Nothing */ }
        end_flag = 1;
    }
    if ((matrix[0][2] != ' ') && (matrix[0][2] == matrix[1][1]) && (matrix[1][1] == matrix[2][0])) {
        cout << endl << "Right Diagonal Matched /" << endl;
        if (1 == player_flag) {
            cout << "[ " << player1_name << " ] Has Won !!!!!!!" << endl;
            player1_score++;
            player_flag = 0;
        }
        else if (0 == player_flag) {
            cout << "[ " << player2_name << " ] Has Won !!!!!!!" << endl;
            player2_score++;
            player_flag = 1;
        }
        else { /* Nothing */ }
        end_flag = 1;
    }


    for (int i = 0; i < MATRIX_ROWS; i++)
    {
        for (int j = 0; j < MATRIX_COLS; j++)
        {
            if (matrix[i][j] == ' ') {
                // There is an empty space, game can continue
                // Switch to the other player
                return;
            }
        }
    }
    cout << "TIE !!!!!!! [ No Winners ]" << endl;
    end_flag = 1;

}

void XOGame::reset_game() {
    for (int i = 0; i < MATRIX_ROWS; i++)
    {
        for (int j = 0; j < MATRIX_COLS; j++)
        {
            matrix[i][j] = ' ';
        }
        cout << endl;
    }
    displayMatrix();
    end_flag = 0;
}

bool XOGame::isGameEnded() {
    if (0 == end_flag) return false;
    else return true;

}
