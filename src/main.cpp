#include "Board.h"

#include <iostream>
#include <filesystem>
#include <assert.h>

void test() {
    Board sudoku = Board("../tests/files/two_solutions.txt");
    sudoku.solve();
    assert(sudoku.get_num_solutions() > 1);
    assert(sudoku.level_to_str() == "Medium");

    Board sudoku2 = Board("../tests/files/easy.txt");
    sudoku2.solve();
    assert(sudoku2.get_num_solutions() == 1);
    assert(sudoku2.level_to_str() == "Easy");
}

void run(Board &sudoku) {
    std::cout << "NEW GAME\nLEVEL: "<< sudoku.level_to_str()<< "\n";
    sudoku.print();
    sudoku.solve();
    std::cout << "SOLUTION\n";
    int num_sols = sudoku.get_num_solutions();
    if (num_sols == 1) {
        sudoku.print_soln();
    } else if (num_sols > 1){
        std::cout << "Sudoku board is invalid as it has more than one solution.\n";
    } else {
        std::cout << "Sudoku board is invalid as it has no solution.\n";
    }
}
void load_board(std::string path) {
    Board sudoku = Board(path);
    run(sudoku);
}

void new_board(int difficulty) {
    Board sudoku(difficulty);
    run(sudoku);
}

int main() {
    test();

    int mode;
    std::cout << "Welcome to SUDOKU.\nEnter 1 for a new game or 2 to load a game from file\n";
    std::cin >> mode;

    if (mode == 1) {
        int level;
        std::cout << "Enter level:\n1 for Easy\n2 for Medium\n3 for Hard\n";
        std::cin >> level;
        if (level < 1 || level > 3) {
            std::cout << "Level must be either 1, 2 or 3. Try again.\n";
            return 1;
        }
        new_board(level);
    } else if (mode == 2) {
        std::string path;
        std::cout << "Enter path to Sudoku file\n";
        std::cin >> path;
        if (!std::filesystem::exists(path)) {
            std::cout << "File does not exist. Try again.\n";
            return 1;
        }
        load_board(path);
    } else {
        std::cout << "Mode must be either 1 (new game) or 2 (load game from file)\n";
        return 1;
    }

    return 0;
}