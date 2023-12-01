#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

constexpr auto MATRIX_ROWS = 3;
constexpr auto MATRIX_COLS = 3;
constexpr auto MAX_PLAYER_NAME_LENGTH = 25;



class XOGame
{
private:
    char matrix[MATRIX_ROWS][MATRIX_COLS];
    string player1_name, player2_name, player_turn;
    char end_flag;
    int row, col, match_number;
    int player1_score = 0, player2_score = 0, player_flag = 0;

public:
    XOGame();
    void displayMatrix();
    void setPlayersNames();
    void displayScore();
    void play();
    void reset_game();
    bool isInputValid();
    bool isGameEnded();
};

