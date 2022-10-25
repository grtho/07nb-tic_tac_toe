//
// Created by Griffin Thompson on 10/25/22.
//


#include <sstream>

#include "TTTGrid.hpp"

using std::endl;
using std::ostream;

TTTGrid::TTTGrid() {
    // init ttt grid. everything is Neither
    // what board looks like:
    //
    // -------------------------------------------
    // |  (nothing)  |  (nothing)  |  (nothing)  |
    // |             |            |              |
    // |             |            |              |
    // |  (nothing)  |  (nothing)  |  (nothing)  |
    // |             |            |              |
    // |             |            |              |
    // |  (nothing)  |  (nothing)  |  (nothing)  |
    // -------------------------------------------
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++) {
            grid[i][j] = Neither;
        }
    }
    // X always goes first. (We call switchPlayer immediately in the game loop inside the driver)
    player = O;
}

void TTTGrid::switchPlayer() {
    if (player == X)
        player = O;
    else
        player = X;
}
// the location of each grid space is numbered 1-9 just like
// any phone keypad. 0 is not a valid choice.
void TTTGrid::placeMark(size_t location) {
    size_t column = location % 3; // locations 1, 4, and 7 will all affect grids in the first column, 2, 5, and 8 column 2, and so forth
    size_t row = location / 3; // int division truncates


    // arrays start at 0, and size_t can't be less than 0
    if (column == 0)
        column = 2; // wrap around from 0 to 2
    else
        column -= 1;

    // most of the time we're okay with the truncation resulting from integer division, i.e. 4 / 3 = 1 (array indice),
    // so this mark will be placed in the 2nd row. this does encounter a snag, however, when we have numbers that are
    // a multiple of 3. 3/3 = 1, but it's not on the 2nd row. likewise, 6/3 = 2, but it is not a location on
    // the 3rd row. Finally, 9/3 = 3, and we don't even have a 4th row. The solution to this is simply to check if our
    // location is a multiple of 3, and if so, shift the row that gets modified up by one.
    if (location % 3 == 0)
        row -= 1;

    grid[row][column] = player;
}
WinInfo TTTGrid::winInfo() {
    WinInfo info{};
    // horizontal
    for (size_t row = 0; row < SIZE; row++) {
        if (grid[row][0] == player
        && grid[row][1] == player
        && grid[row][2] == player) {
            info.won = true;
            info.direction = Horizontal;
            return info;
        }
    }

    // vertical
    for (size_t col = 0; col < SIZE; col++) {
        if (grid[0][col] == player
        && grid[1][col] == player
        && grid[2][col] == player) {
            info.won = true;
            info.direction = Vertical;
            return info;
        }
    }

    // diagonal
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) {
        info.won = true;
        info.direction = Diagonal;
        return info;
    }

    info.won = false;
    info.direction = None;
    return info;
}

TTTOption TTTGrid::getCurrentPlayer() {
    return player;
}

ostream& operator <<(ostream& os, const TTTGrid& tttGrid) {
    std::stringstream sStream;
    const std::string divider = "+-----+-----+-----+";
    // beginning of the table
    sStream << divider << "\n";

    for (size_t row = 0; row < tttGrid.SIZE; row++) {
        for (size_t col = 0; col < tttGrid.SIZE; col++) {
            sStream << "|  " << TTTGrid::optionAsChar(tttGrid.grid[row][col]) << "  ";
        }
        sStream << "|\n";
        if (row + 1 != tttGrid.SIZE)
            sStream << divider << "\n";
    }
    sStream << divider;

    os << sStream.str();
    return os;
}

char TTTGrid::optionAsChar(const TTTOption& option) {
    switch (option) {
        case X:
            return 'X';
        case O:
            return 'O';
        case Neither:
            return ' ';
    }
}

// +-----+-----+-----+
// |  X  |     |     |
// +-----+-----+-----+
// |     |     |     |
// +-----+-----+-----+
// |     |     |     |
// +-----+-----+-----+
