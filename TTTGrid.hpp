//
// Created by Griffin Thompson on 10/25/22.
//

#ifndef INC_07NB_TIC_TAC_TOE_TTTGRID_HPP
#define INC_07NB_TIC_TAC_TOE_TTTGRID_HPP

#include <iostream>

using std::endl;
using std::ostream;

enum TTTOption {X = 'X', O = 'O', Neither};
enum WinDirection { Horizontal, Vertical, Diagonal, None };
struct WinInfo {
    bool won;
    WinDirection direction;
};

class TTTGrid {
public:
    const int SIZE = 3;
    TTTGrid();

    void switchPlayer();
    void placeMark(size_t);

    WinInfo winInfo();
    TTTOption getCurrentPlayer();
    friend ostream& operator <<(ostream&, const TTTGrid&);

    static char optionAsChar(const TTTOption&);

private:
    TTTOption grid[3][3]{};
    TTTOption player;

};


#endif //INC_07NB_TIC_TAC_TOE_TTTGRID_HPP
