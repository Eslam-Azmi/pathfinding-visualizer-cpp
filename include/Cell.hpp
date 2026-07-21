#ifndef CELL_HPP
#define CELL_HPP

enum class cellState {
    empty,
    wall,
    start,
    end,
    visited,
    path,
    mud
};

struct Cell {
    int row;
    int col;
    cellState state = cellState::empty;

    int gCost = 1e9;  //ground cost
    int fCost = 1e9;  // full esitmated cost
    Cell* parent = nullptr;
};

#endif