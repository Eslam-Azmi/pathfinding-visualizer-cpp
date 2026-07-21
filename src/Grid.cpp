#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Grid.hpp"
using namespace std;

Grid::Grid(int gridSize, float cellSize)
    : gridSize_(gridSize), cellSize_(cellSize), cells_(gridSize, vector<Cell>(gridSize)){

        for (int r = 0; r < gridSize_; r++) {
            for (int c = 0; c < gridSize_; c++) {
                cells_[r][c].row = r;
                cells_[r][c].col = c;
            }
        }

        cellShape_.setSize({cellSize_ - 1.0f, cellSize_ - 1.0f});
        cellShape_.setOutlineColor(sf::Color::White);
        cellShape_.setOutlineThickness(-0.5f);
}

void Grid::draw(sf::RenderWindow& window){
    for (int r = 0; r < gridSize_; r++){
        for (int c = 0; c < gridSize_; c++){
            cellShape_.setPosition({c*cellSize_, r*cellSize_});

            switch(cells_[r][c].state){
                case cellState::empty:
                    cellShape_.setFillColor(sf::Color(30, 30, 30)); break;
                case cellState::wall:
                    cellShape_.setFillColor(sf::Color(80, 80, 80)); break;
                case cellState::start:
                    cellShape_.setFillColor(sf::Color::Green); break;
                case cellState::end:
                    cellShape_.setFillColor(sf::Color::Red); break;
                case cellState::visited:
                    cellShape_.setFillColor(sf::Color(0, 100, 150)); break;
                case cellState::path:
                    cellShape_.setFillColor(sf::Color::Yellow); break;
                case cellState::mud:
                    cellShape_.setFillColor(sf::Color(165, 42, 42)); break;
            }

            window.draw(cellShape_);
        }
    }
}

void Grid::hardReset(pair<int,int>& lastStart, pair<int,int>& lastEnd){
    for (int r = 0; r < gridSize_; r++){
        for (int c = 0; c < gridSize_; c++){
            cells_[r][c].state = cellState::empty;
            cells_[r][c].gCost = 1e9;
            cells_[r][c].fCost = 1e9;
            cells_[r][c].parent = nullptr;
        }
    }
    lastStart = {-1, -1};
    lastEnd = {-1, -1};
}

void Grid::softClear(pair<int,int>& lastStart, pair<int,int>& lastEnd){
    for (int r = 0; r < gridSize_; r++){
        for (int c = 0; c < gridSize_; c++){
            cells_[r][c].gCost = 1e9;
            cells_[r][c].fCost = 1e9;
            cells_[r][c].parent = nullptr;

            if (cells_[r][c].state == cellState::visited || cells_[r][c].state == cellState::path){
                cells_[r][c].state = cellState::empty;
            }
        }
    }
}

void Grid::handlePainting(sf::RenderWindow& window, bool starting, bool ending, bool walling, bool mudding, pair<int,int>& lastStart, pair<int,int>& lastEnd){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    int r = mousePos.y / cellSize_;
    int c = mousePos.x / cellSize_;

    if (r >= 0 && r < gridSize_ && c >= 0 && c < gridSize_){
        Cell& targetCell = cells_[r][c];

        if (starting){
            if (lastStart.first != -1){
                cells_[lastStart.first][lastStart.second].state = cellState::empty;
            }

            targetCell.state = cellState::start;
            lastStart = {r,c};
        }else if (ending){
            if (lastEnd.first != -1){
                cells_[lastEnd.first][lastEnd.second].state = cellState::empty;
            }

            targetCell.state = cellState::end;
            lastEnd = {r,c};
        }else if(walling){
            if (targetCell.state == cellState::empty) {
                targetCell.state = cellState::wall;
            }
        }else if (mudding){
            if (targetCell.state == cellState::empty) {
                targetCell.state = cellState::mud;
            }
        }else {
            if (targetCell.state == cellState::wall || targetCell.state == cellState::mud){
                targetCell.state = cellState::empty;
            }
        }
    }
}
    
