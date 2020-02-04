# Sudoku Solver

## About

A recursive solver for sudoku puzzles written in C.

## Getting Started (Linux)

1. Clone the repository

```shell
    $ git clone https://github.com/garroadran/sudokusolver.git
```

2. CD into the repository directory

```shell
    $ cd sudokusolver
```

3. Compile the source code using GCC.

```shell
    $ gcc -Wall sudoku.c -o sudokuSolver
```

4. Execute the compiled application

```shell
    $ ./sudokuSolver
```

## Command Line Arguments

### -n

Specifies a particular puzzle to solve from the `grids` file. If this option is not included, a random puzzle will be selected.

__Example__

```shell
    $ ./sudokuSolver -n 32
```

### -h

Display a simple help menu.

## Additional Puzzles

Including additional puzzles is not yet as simple as simply adding them to the `grids` file. The `TOTAL_PUZZLE_COUNT` constant in `sudoku.c` needs to be updated with the total count of puzzles, and therefore the program will need to be recompiled.
