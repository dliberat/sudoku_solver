#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "business.h"

int checkBox(int xIndex, int yIndex, int (*grid)[9]);
int checkCol(int col, int (*grid)[9]);
int checkRow(int row[]);
int checkState(int (*grid)[9]);
void findNextOpen(int *x, int *y, int (*grid)[9]);
int parseArgs(int argc, char** argv);
void printGrid(int (*grid)[9]);
void readFile(FILE *fp, int realPuzzleNo, int (*grid)[9]);
int readGridFromFile(int puzzleNo, int (*grid)[9]);
int solve(int x, int y, int (*grid)[9]);
void solveAndDisplay(int (*grid)[9]);

/**
 * The total number of puzzles available in the grids file.
 */
#define TOTAL_PUZZLE_COUNT 51


int main(int argc, char** argv)
{
    int puzzleNo = parseArgs(argc, argv);

    if (puzzleNo > -1)
    {
        int grid[9][9];
        int success = readGridFromFile(puzzleNo, grid);

        if (success == 0)
        {
            solveAndDisplay(grid);
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

/**
 * Handle command-line arguments.
 * Supported arguments:
 * [none]       (Solve a random puzzle)
 * -n [int]     (Specify a puzzle number)
 * -h           (Display help menu)
 */
int parseArgs(int argc, char** argv)
{
    int retval = -1;

    int opt;
    while((opt = getopt(argc, argv, "n:h")) != -1)
    {
        switch(opt)
        {
            case 'n':
                retval = atoi(optarg);
                break;
            case 'h':
                printf("Sudoku Solver (March 2019)\n");
                printf("Options:\n");
                printf("  [no options]\t(Solve a random puzzle)\n");
                printf("  -h\t\t(Show this help menu)\n");
                printf("  -n [int]\t(Solve a specific puzzle)\n");
                break;
        }
    }

    // Assign a random puzzle number
    // if one was not specified
    if (argc == 1)
    {
        srand(time(NULL));
        retval = rand() % TOTAL_PUZZLE_COUNT;
    }

    return retval;
}

/**
 * Displays the sudoku grid in the console.
 */
void printGrid(int (*grid)[9])
{
    int y;

    printf("-----------------------------\n");

    for (y = 0; y < 9; y++)
    {
        printf("|%d, %d, %d | %d, %d, %d | %d, %d, %d|\n",
            grid[y][0], grid[y][1], grid[y][2], 
            grid[y][3], grid[y][4], grid[y][5], 
            grid[y][6], grid[y][7], grid[y][8]);

        if (y % 3 == 2)
        {
            printf("-----------------------------\n");
        }
    }
}

/**
 * Read the grids file line by line until it finds a line
 * that matches the pattern "Grid [puzzleNo]\n".
 * After that, it reads the next 9 lines and interprets them
 * as rows of a sudoku puzzle, which it loads into the
 * grid argument.
 */
void readFile(FILE *fp, int realPuzzleNo, int (*grid)[9])
{
    int MAXCHAR = 128;
    char line[MAXCHAR];

    // keyBuffer stores the string that identifies
    // the position of grid # puzzleNo in the grids file.
    // The file will be read incrementally until reaching
    // a line that matches the string in keyBuffer.
    char keyBuffer[12];
    sprintf(keyBuffer, "Grid %d\n", realPuzzleNo);

    int toRead = -1;
    int *ptr = &grid[0][0];
    int i;

    while (fgets(line, MAXCHAR, fp) != NULL)
    {
        // Once the correct position of the grid
        // in the file is identified, read off the
        // next 9 lines as integer values and
        // place them in the grid.
        if (toRead > 0)
        {
            for (i=0;i<9;i++)
            {
                int digit = line[i] - 48;
                *ptr = digit;
                ptr++;
            }

            toRead--;
        }

        if (toRead == 0)
        {
            break;
        }

        // Found the grid we're looking for.
        // Start the counter for the lines that
        // contain the grid numbers
        if (strcmp(line, keyBuffer) == 0)
        {
            toRead = 9;
        }
        
    }
}

/**
 * Finds the specified puzzle in the grids file,
 * and loads it into the grid array.
 */
int readGridFromFile(int puzzleNo, int (*grid)[9])
{
    // Modulo so that any given puzzleNo will
    // return a puzzle.
    int realPuzzleNo = puzzleNo % TOTAL_PUZZLE_COUNT;

    FILE *fp;
    char* filename = "./grids";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open grid information file.\n");
        return 1;
    }
    else
    {
        readFile(fp, realPuzzleNo, grid);
    }

    fclose(fp);

    return 0;
}

/**
 * Displays the starting grid in the console,
 * searches for a solution, then prints the
 * final solved (or incomplete, if impossible) grid.
 */
void solveAndDisplay(int (*grid)[9])
{
    printf("   ---- Starting Grid ----\n");
    printGrid(grid);
    printf("\n");

    int result;
    result = solve(0, 0, grid);
    
    if (result == 1)
    {
        printf("       ---- Failed ----\n\n");
    }
    else if (result == 0)
    {
        printf("    ---- Solved it! ----\n\n");
    }

    printGrid(grid);
}

