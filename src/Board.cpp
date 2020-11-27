#include "Board.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <limits.h>

// Board characters must be between 0-9.
bool is_valid_cell(char c) {
    int num = c - '0';
    return num >= 0 && num <= 9;
}

// Initialize a new sudoku board
Board::Board(int difficulty) {
    // num of empty spaces on the board
    switch (difficulty) {
        case 1:
            level = Easy;
            break;
        case 2:
            level = Medium;
            break;
        case 3:
            level = Hard;
            break;
        default:
            std::cout << "Invalid Level.";
            return;
    }

    int remove = level;
    // limit the number of tries here so it doesnt loop forever.
    // TODO: Figure out a good value for this.
    auto max = INT_MAX;
    board = std::vector(size, std::vector<int>(size, 0));
    solve();
    srand((unsigned) time(0));

    while (remove && max) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (!board[row][col]) {
            max--;
            continue;
        }

        int original = board[row][col];
        board[row][col] = 0;
        // TODO: Figure a way to do this with less copying.
        temp = board;
        solve();

        // check if removing this cell breaks the sudoku or has no solution.
        if (num_solutions != 1) {
            board[row][col] = original;
        } else {
            remove--;
        }
        max--;
    }
    //TODO: Shuffle board randomly within grid limits.
    board = temp;
}

// Load board from file.
Board::Board(std::string path) {
    std::ifstream file(path);
    if (!file) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    int empty_count = 0;

    std::string line;
    while (std::getline(file, line)) {
        if (line.length() != size) {
            std::cout << "Invalid board. Should be 9x9.\n";
            return;
        }

        std::vector<int> row;
        for (auto const &c : line) {
            if (is_valid_cell(c)) {
                if (c == '0') {
                    empty_count++;
                }
                row.push_back(c - '0');
            } else {
                std::cout << "Invalid character. must be 1-9 or 0 for unfilled\n";
                return;
            }
        }
        board.push_back(std::move(row));
    }
    if (board.size() != size) {
        std::cout << "Invalid board. Should be 9x9.\n";
    }

    // Classify level
    if (empty_count <= Easy) {
        level = Easy;
    } else if (empty_count <= Medium) {
        level = Medium;
    } else {
        level = Hard;
    }

}

bool Board::check_constraints(int row, int col) {
    int val = board[row][col];
    for (int col_i = 0; col_i < size; col_i++) {
        int check = board[row][col_i];
        if (check && col_i != col && board[row][col_i] == val) {
            return false;
        }
    }

    for (int row_i = 0; row_i < size; row_i++) {
        int check = board[row_i][col];
        if (check && row_i != row && board[row_i][col] == val) {
            return false;
        }
    }

    // Note: this is hardcoded for size = 9.
    int sq_row_start = (row / 3) * 3;
    int sq_col_start = (col / 3) * 3;

    for (int i = sq_row_start; i < sq_row_start + 3; i++) {
        for (int j = sq_col_start; j < sq_col_start + 3; j++) {
            if (i != row && j != col) {
                if (board[i][j] == val) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::solve(int row, int col) {
    // found a solution.
    if (row == size) {
        num_solutions += 1;
        return true;
    }
    // reached end of a column.
    if (col == size) {
        return solve(row+1, 0);
    }
    // not yet set.
    if (board[row][col] == 0) {
        for (char num = 1; num <= 9; num++) {
            board[row][col] = num;
            if (check_constraints(row, col) && solve(row, col+1)) {
                if (num_solutions > 1) {
                    // stop looking
                    return true;
                }
                soln = board;
            }
            // undo.
            board[row][col] = 0;

        }
    } else {
        // skip this [row][col]
        return solve(row, col+1);
    }

    return false;
}

void Board::solve() {
    // start from first cell.
    num_solutions = 0;
    solve(0, 0);
}

void Board::print_soln() {
    for (auto const &row : soln) {
        for (auto const &val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-----------------\n";
}


void Board::print() {
    for (auto const &row : board) {
        for (auto const &val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-----------------\n";
}

std::string Board::level_to_str() {
    switch (level) {
        case Easy:
            return "Easy";
        case Medium:
            return "Medium";
        case Hard:
            return "Hard";
        default:
            return "Unknown";
    }
}

int Board::get_num_solutions() {
    return num_solutions;
}