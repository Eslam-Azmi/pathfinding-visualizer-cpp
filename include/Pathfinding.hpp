#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include <queue>
#include <vector>
#include "Grid.hpp"
using namespace std;

struct compareCells {
    bool operator()(const Cell* a, const Cell* b){
        return a->distance > b->distance;
    }
};

class Pathfinding{
    private:
        priority_queue<Cell*, vector<Cell*>, compareCells> pq_;
        
        bool running_;
        bool pathFound_;
        pair<int,int> startPos_;
        pair<int,int> endPos_;

        Cell* path = nullptr;

    public:
        Pathfinding();

        bool isRunning() const {return running_;}
        bool isPathFound() const {return pathFound_;}

        void startSearch(Grid& grid, pair<int,int> startPos, pair<int,int> endPos);

        void step(Grid& grid);
        void pathing(Grid& grid);

        void reset();
};

#endif