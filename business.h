/**
 * Checks whether the 3x3 sector that a given index
 * is located in contains any repeated numbers.
 * Returns 0 if there are no errors.
 * Returns 1 if there are duplicate numbers
 * in the box.
 */
int checkBox(int xIndex, int yIndex, int (*grid)[9])
{
    int currentValue;
    int values[10] = {0};

    int mod3 = xIndex % 3;
    int xLoBound = xIndex - mod3;
    int xUpBound = xIndex + 2 - mod3;

    mod3 = yIndex % 3;
    int yLoBound = yIndex - mod3;
    int yUpBound = yIndex + 2 - mod3;

    int x;
    int y;
    for (x = xLoBound; x <= xUpBound; x++)
    {
        for (y = yLoBound; y <= yUpBound; y++)
        {
            currentValue = grid[y][x];
            if (currentValue == 0)
            {
                continue;
            }
            else if (values[currentValue] == 1)
            {
                return 1;
            }
            else
            {
                values[currentValue] = 1;
            }
        }
    }

    return 0;
}

/**
 * Checks if a single column in the grid has errors.
 * Returns 0 if the column has no errors.
 * Returns 1 if the same number appears multiple
 * times in the same column.
 */
int checkCol(int col, int (*grid)[9])
{
    int values[10] = {0};
    int y;
    int currentValue;

    for(y=0;y<9;y++)
    {
        currentValue = grid[y][col];
        if (currentValue == 0)
        {
            continue;
        }
        else if (values[currentValue] == 1)
        {
            return 1;
        }
        else
        {
            values[currentValue] = 1;
        }
    }
    return 0;
}

/**
 * Checks if a row has errors on it.
 * Returns 0 if  the row has no errors.
 * Returns 1 if the row has duplicate numbers.
 */
int checkRow(int row[])
{
    int values[10] = {0};
    int x;
    int currentValue;

    for (x=0;x<9;x++)
    {
        currentValue = row[x];
        if (currentValue == 0) 
        {
            continue;
        }
        else if (values[currentValue] == 1)
        {
            return 1;
        }
        else
        {
            values[currentValue] = 1;
        }
    }
    return 0;
}

/**
 * Checks the current configuration of the grid
 * to see if there are any errors anywhere.
 */
int checkState(int (*grid)[9])
{
    int x;
    for (x=0;x<9;x++)
    {
        if (checkRow(grid[x]) == 1)
        {
            return 1;
        }
        if (checkCol(x, grid) == 1)
        {
            return 1;
        }
    }

    for (x=0;x<9;x+=3)
    {
        if (checkBox(x, 0, grid) == 1 ||
            checkBox(x, 3, grid) == 1 ||
            checkBox(x, 6, grid) == 1)
            {
                return 1;
            }
    }

    return 0;
}

/**
 * Modifies x and y to point to the next grid
 * space that contains a zero.
 * 
 * If there are no remaining empty spaces,
 * the resulting values will be x=8, y=9.
 */
void findNextOpen(int *x, int *y, int (*grid)[9])
{
    while (*y < 9)
    {
        while (*x < 9)
        {
            if (grid[*y][*x] == 0)
            {
                return;
            }

            *x = *x + 1;
        }

        *x = 0;
        *y = *y+1;
    }
}

/**
 * Modifies a grid, searching for a valid solution
 * to the puzzle.
 * 
 * Returns 0 if the puzzle was successfully solved.
 * Returns 1 if the puzzle contains errors and
 * cannot be solved.
 */
int solve(int x, int y, int (*grid)[9])
{
    findNextOpen(&x, &y, grid);
    if (y == 9)
    {
        // solved!
        return 0;
    }

    // try a number
    int value;
    for (value = 1; value <= 9; value++)
    {
        grid[y][x] = value;

        if (checkState(grid) == 1)
        {
            grid[y][x] = 0;
            continue;
        }
        else if (solve(x, y, grid) == 0)
        {
            // solved!
            return 0;
        }

        grid[y][x] = 0;   
    }

    return 1;

}
