#pragma once

#include <vector>
#include <string>

class Board {

    enum Level {
        Easy = 49,
        Medium = 53,
        Hard = 57
    };

    // 9x9 board
    int size = 9;
    int num_solutions = 0;
    Level level;

    // working board.
    std::vector<std::vector<int>> board;
    // if we find a solution, store it here.
    std::vector<std::vector<int>> soln;
    // store temp boards for making a sudoku game.
    std::vector<std::vector<int>> temp;

    bool check_constraints(int row, int col);
    bool solve(int row, int col);

public:
    Board(std::string path);
    Board(int level = 1);
    ~Board() = default;
    void solve();
    void print();
    void print_soln();
    std::string level_to_str();
    int get_num_solutions();
};
