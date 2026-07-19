#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.hpp"
using namespace std;

class Grid{
    private: 
        int gridSize_;
        float cellSize_;
        vector<vector<Cell>> cells_;
        sf::RectangleShape cellShape_;

    public:
        Grid(int gridSize, float cellSize);

        int getSize() const {return gridSize_;}
        Cell& getCell(int r, int c) {return cells_[r][c];}
        const Cell& getCell(int r, int c) const {return cells_[r][c];}

        void draw(sf::RenderWindow& window);

        void hardReset(pair<int,int>& lastStart, pair<int,int>& lastEnd);
        void softClear(pair<int,int>& lastStart, pair<int,int>& lastEnd);
        void handlePainting(sf::RenderWindow& window,  bool starting, bool ending, bool walling,
                            pair<int,int>& lastStart, pair<int,int>& lastEnd);
};

#endif