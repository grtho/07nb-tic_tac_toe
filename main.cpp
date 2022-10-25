#include <iostream>
#include "TTTGrid.hpp"

using std::cout;
using std::cin;
using std::endl;

int main() {
    TTTGrid grid;

    std::cout << "Welcome to TicTacToe."
              << "\nInstructions: the locations on the TicTacToe grid are numbered 1-9;"
              << "\n1 is the top left square, 9 is the bottom right square and 5 is the center center square."
              << "\nTry to get three of your marks in a row vertically, horizontally, or diagonally."
              << "\nGood Luck!"
              << std::endl;

    while (!grid.winInfo().won) {
        grid.switchPlayer();
        std::cout <<  grid << std::endl;
        size_t bl;
        cin >> bl;

        grid.placeMark(bl);

    }

    std::string direction;

    switch (grid.winInfo().direction) {

        case Horizontal:
            direction = "horizontally";
            break;
        case Vertical:
            direction = "vertically";
            break;
        case Diagonal:
            direction = "diagonally";
            break;
        case None:
            direction = "N0n3-41ly";
            break;
    }

    std::cout << "Player controlling mark '" << TTTGrid::optionAsChar(grid.getCurrentPlayer()) << "' wins " << direction << "!" << std::endl;

    std::cout << grid;
}