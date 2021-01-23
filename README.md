# sudoku-solver

Sudoku solver implemented using AC-3 Algorithm and Minimum Remaining Values Heuristic

## Building

To build just use the makefile included at the root of this repository.

```
make
```

## Usage

The program takes the sudoku puzzles from the console, so you can run something like the following to get the results from an input file

```
cat testCases/1.in | ./sudoku_solver
```

The format of the input is 9 rows of 9 numbers each, just like the examples in the testCases directory. If the value of a cell in the grid is unknown, use 0 to represent it.

Example:

```
510690007
600718359
009524068
100470206
736280904
402301070
860107592
241956783
957800041
```

Output:

```
Output:
-------------------------------
| 5  1  8 | 6  9  3 | 4  2  7 |
-         -         -         -
| 6  2  4 | 7  1  8 | 3  5  9 |
-         -         -         -
| 3  7  9 | 5  2  4 | 1  6  8 |
-------------------------------
| 1  8  5 | 4  7  9 | 2  3  6 |
-         -         -         -
| 7  3  6 | 2  8  5 | 9  1  4 |
-         -         -         -
| 4  9  2 | 3  6  1 | 8  7  5 |
-------------------------------
| 8  6  3 | 1  4  7 | 5  9  2 |
-         -         -         -
| 2  4  1 | 9  5  6 | 7  8  3 |
-         -         -         -
| 9  5  7 | 8  3  2 | 6  4  1 |
-------------------------------
```
