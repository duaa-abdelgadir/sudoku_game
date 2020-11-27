# Japanese Sudoku

This program allows a user to load a predefined 9*9 sudoku board and solves it.
Users can also load a new game to solve.

## Prerequisites
Developed with:
* c++17
* gcc10
## Building
```
g++-10 src/main.cpp src/Board.cpp -o sudoku
```

## Usage

```
./sudoku
Welcome to SUDOKU.
Enter 1 for a new game or 2 to load a game from file
1
Enter level:
1 for Easy
2 for Medium
3 for Hard
2
NEW GAME
1 2 3 4 5 6 7 8 9 
0 0 6 7 8 9 0 0 3 
7 8 9 0 0 3 4 5 6 
0 0 4 3 0 5 8 0 7 
3 6 5 0 0 7 2 1 1 
8 0 7 2 1 0 3 6 0 
5 3 1 6 4 0 9 7 0 
6 4 0 9 7 1 5 0 0 
0 0 2 0 3 8 0 1 4 
-----------------
SOLUTION
1 2 3 4 5 6 7 8 9 
4 5 6 7 8 9 1 2 3 
7 8 9 1 2 3 4 5 6 
2 1 4 3 6 5 8 9 7 
3 6 5 8 9 7 2 1 1 
8 9 7 2 1 4 3 6 5 
5 3 1 6 4 2 9 7 8 
6 4 8 9 7 1 5 3 2 
9 7 2 5 3 8 6 1 4 
-----------------
```

## Documentation / TODOs:

**Level Classification:** Currently, levels are classified only based on
the number of cells which the player has to fill in. I would like to add
support for also factoring in symmetry of numbers into the difficulty
evaluation.

**New games:** Currently, the generated new game will always have the same
solution due to the fact that it will always use the the
same initial solution to generate a new board. Ideally, it would randomly
choose from one of the many solutions that an empty board can generate in 
order to provide variation. I would also try to randomly move around columns/rows
within the same constraints (remains in the same grid in order not to break rules)
for more variation.

**Symmetry** Currently the symmetry of the board is random so a uniform
symmetry is not guaranteed. I'd like to investigate the c++ random.h library
to see if there are any distributions that would help make the board more
symmetric.