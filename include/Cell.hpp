#ifndef CELL_HPP
#define CELL_HPP

enum class cellState {
    empty,
    wall,
    start,
    end,
    visited,
    path
};

struct Cell {
    int row;
    int col;
    cellState state = cellState::empty;

    int distance = 0;
    Cell* parent = nullptr;
};

#endif