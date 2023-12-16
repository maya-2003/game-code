// Class definition for Pyramic_Board class
// Author: Maya Ahmed Rady
// ID: 20220269
// Section: S3
// Date: 12/7/2023
// Version: 1
#include <iostream>
#include <random>
#include <iomanip>
#include "BoardGame_Classes.hpp"
#include <vector>
using namespace std;

Pyramic_Board::Pyramic_Board() {
    n_rows = 3;
    board = new char*[n_rows];
    board[0] = new char[1];
    board[1] = new char[3];
    board[2] = new char[5];

    // fill in all the board with blank space
    for (int i = 0; i < 1; ++i) {
        board[0][i] = ' ';
    }
    for (int i = 0; i < 3; ++i) {
        board[1][i] = ' ';
    }
    for (int i = 0; i < 5; ++i) {
        board[2][i] = ' ';
    }
}

bool Pyramic_Board::check_boundry(int chosenRow, int chosenColumn) {
    // get the number of columns in each row
    int noOfColumns;
    if(chosenRow==0){
        noOfColumns=1;
    }
    else if(chosenRow==1){
        noOfColumns=3;
    }
    else{
        noOfColumns=5;
    }

    // Check if the chosen row is out of the board boundry
    if (chosenRow < 0 || chosenRow >= n_rows){
        return false;
    }

    // Check if the chosen column is out of the board boundry
    if(chosenColumn < 0 || chosenColumn >= noOfColumns ){
        return false;
    }

    // Check if the cell is not empty
    if(board[chosenRow][chosenColumn] != ' '){
        return false;
    }
    return true;
}

bool Pyramic_Board::update_board(int chosenRow, int chosenColumn, char mark) {
    char player = toupper(mark);
    if (check_boundry(chosenRow, chosenColumn)) {
            board[chosenRow][chosenColumn] = player;
            n_moves++;
            return true;
    }
    // return false if the column or row number is out of boundry or the cell is not empty
    return false;
}

void Pyramic_Board::construct_row(int row_index) {
    // get number of columns in the row
    int noOfColumns;
    if(row_index==0){
        noOfColumns=1;
    }
    else if(row_index==1){
        noOfColumns=3;
    }
    else{
        noOfColumns=5;
    }
    // number of total characters in a row
    int rowTotalCharacters = cell_caharacters * noOfColumns;
    // calculate padding for each row to align the rows
    int length_diff = base - noOfColumns;
    int padding = length_diff * (cell_caharacters / 2);

    cout << setw(padding) << setfill(' ');
    for (int j = 0; j < noOfColumns; j++) {
        cout << "| (" << row_index << "," << j << ") " << board[row_index][j];
    }
    cout << " |" << endl;
    cout << setw(padding+rowTotalCharacters) << setfill(' ');
    cout<< setw(rowTotalCharacters) << ' ' << setfill(' ') << endl;
}

void Pyramic_Board::display_board() {
    for (int i = 0; i < n_rows; i++) {
        construct_row(i);
    }
}

bool Pyramic_Board::check_scenario(vector<vector<int>> scenario) {
    // get the character in the first cell of the winning scenarios
    char square_one = board[scenario[0][0]][scenario[0][1]];
    // check if it's empty and if so return false because then it will not match a winning scenario
    if (square_one == ' ') {
        return false;
    }
    for (auto square : scenario) {
        int rowIndex = square[0];
        int columnIndex = square[1];
        // check if the chosen square is different from square one because if so then it will not be a winning scenario
        if (board[rowIndex][columnIndex] != square_one) {
            return false;
        }
    }

    // If all cells in the scenario have the same non-empty character then it's true that it's a winning scenario
    return true;
}


bool Pyramic_Board::is_winner() {
    vector<vector<vector<int>>> winningScenarios = {{{0, 0}, {1, 0}, {2, 0}},{{0, 0}, {1, 2}, {2, 4}},{{2, 1}, {2, 2}, {2, 3}},{{0, 0}, {1, 1}, {2, 2}},{{2, 0}, {2, 1}, {2, 2}},{{1, 0}, {1, 1}, {1, 2}},{{2, 2}, {2, 3}, {2, 4}}};

    // check if there is a match with a winning scenario
    for (auto scenario : winningScenarios) {
        if (check_scenario(scenario)) {
            return true;
        }
    }
    // If no winning scenario match was found
    return false;
}

bool Pyramic_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool Pyramic_Board::game_is_over() {
    return n_moves >= 9;
}
