#include "../include/Pathfinding.hpp"

Pathfinding::Pathfinding()
    : running_(false), pathFound_(false), startPos_({-1,-1}), endPos_({-1,-1}){

    }

void Pathfinding::startSearch(Grid& grid, pair<int,int> startPos, pair<int,int> endPos){
    reset();

    startPos_ = startPos;
    endPos_ = endPos;
    running_ = true;

    int size = grid.getSize();

    for (int r = 0; r < size; r++){
        for (int c = 0; c < size; c++){
            Cell& cell = grid.getCell(r, c);
            cell.distance = 1e9;
            cell.parent = nullptr;

            if (cell.state == cellState::visited || cell.state == cellState::path){
                cell.state = cellState::empty;
            }
        }
    }

    Cell& startCell = grid.getCell(startPos_.first, startPos_.second);
    startCell.distance = 0;

    pq_.push(&startCell);
}

void Pathfinding::step(Grid& grid){
    if (!running_ || pathFound_) return;

    if (pq_.empty()){
        running_ = false;
        return;
    }

    Cell* current = pq_.top();
    pq_.pop();

    if (current->row == endPos_.first && current->col == endPos_.second){
        pathFound_ = true;
        path = current->parent;
        
        return;
    }

    if (current->state != cellState::start && current->state != cellState::end){
        current->state = cellState::visited;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int size = grid.getSize();

    for (int i = 0; i < 4; i++){
        int nr = current->row + dr[i];
        int nc = current->col + dc[i];

        if (nr >= 0 && nr < size && nc >= 0 && nc < size){
            Cell& neighbor = grid.getCell(nr,nc);

            if (neighbor.state == cellState::wall) continue;

            int newDistance = current->distance + 1;

            if (newDistance < neighbor.distance){
                neighbor.distance = newDistance;
                neighbor.parent = current;
                pq_.push(&neighbor);
            }
        }
    }
}

void Pathfinding::pathing(Grid& grid){
    if (path->row == startPos_.first && path->col == startPos_.second){
            pathFound_ = false;
            running_ = false;
            return;
        }
        path->state = cellState::path;
        path = path->parent;
}

void Pathfinding::reset(){
    running_ = false;
    pathFound_ = false;

    priority_queue<Cell*, vector<Cell*>, compareCells> emptyQueue;
    swap(pq_, emptyQueue);
}