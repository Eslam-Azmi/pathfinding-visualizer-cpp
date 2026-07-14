#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

enum class cellState{
    empty,
    wall,
    start,
    end,
    visited,
    path
};

struct Cell{
    int row;
    int col;
    cellState state = cellState::empty;

    int distance = 0;
    Cell* parent = nullptr;
};

int main() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 800;
    
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "A* & Dijkstra Pathfinding Visualizer");
    
    window.setFramerateLimit(60);

    const int GRID_SIZE = 20;
    const float CELL_SIZE = 40.0f;

    vector<vector<Cell>> grid(GRID_SIZE, vector<Cell>(GRID_SIZE));

    for (int r = 0; r < GRID_SIZE; r++){
        for (int c = 0; c < GRID_SIZE; c++){
            grid[r][c].row = r;
            grid[r][c].col = c;
        }
    }

    sf::RectangleShape cellShape({CELL_SIZE - 1.0f, CELL_SIZE - 1.0f});
    cellShape.setOutlineColor(sf::Color::White);
    cellShape.setOutlineThickness(-0.5f);

    bool painting = false;
    bool walling = true;
    bool starting = false;
    bool ending = false;
    bool isSearching = false;
    bool pathing = false;

    pair<int,int> lastStart = {GRID_SIZE-1,GRID_SIZE-1};
    grid[GRID_SIZE-1][GRID_SIZE-1].state = cellState::start;
    pair<int,int> lastEnd = {0,0};
    grid[0][0].state = cellState::end;

    struct Compare {
        bool operator()(Cell* a, Cell* b){
            return a->distance > b->distance;
        }
    };
    priority_queue<Cell*, vector<Cell*>, Compare> pq;

    Cell* root = nullptr;

    while (window.isOpen()) {

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                if (keyPressed->code == sf::Keyboard::Key::S) {
                    starting = true;
                }
                if (keyPressed->code == sf::Keyboard::Key::E) {
                    ending = true;
                }
                if (keyPressed->code == sf::Keyboard::Key::R){
                    for (int r = 0; r < GRID_SIZE; r++){
                        for (int c = 0; c < GRID_SIZE; c++){
                            grid[r][c].state = cellState::empty;
                            grid[r][c].distance = 0;
                            grid[r][c].parent = nullptr;
                        }
                    }
                    grid[lastStart.first][lastStart.second].state = cellState::start;
                    grid[lastEnd.first][lastEnd.second].state = cellState::end;
                    
                    while (!pq.empty()){
                        pq.pop();
                    }
                }
                if (keyPressed->code == sf::Keyboard::Key::C){
                    for (int r = 0; r < GRID_SIZE; r++){
                        for (int c = 0; c < GRID_SIZE; c++){
                            if (grid[r][c].state == cellState::visited || grid[r][c].state == cellState::path){
                                grid[r][c].state = cellState::empty;
                            }
                            grid[r][c].distance = 0;
                            grid[r][c].parent = nullptr;
                        }
                    }
                    grid[lastStart.first][lastStart.second].state = cellState::start;
                    grid[lastEnd.first][lastEnd.second].state = cellState::end;
                    
                    while (!pq.empty()){
                        pq.pop();
                    }
                }
                if (keyPressed->code == sf::Keyboard::Key::Enter){
                    grid[lastStart.first][lastStart.second].state = cellState::visited;
                    grid[lastStart.first][lastStart.second].distance = 0;
                    pq.push(&grid[lastStart.first][lastStart.second]);
                    isSearching = true;
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
                if (keyPressed->code == sf::Keyboard::Key::S) {
                    starting = false;
                }
                if (keyPressed->code == sf::Keyboard::Key::E) {
                    ending = false;
                }
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()){   
                if (mouseButton->button == sf::Mouse::Button::Left){
                    painting = true;
                    walling = true;
                }
                if (mouseButton->button == sf::Mouse::Button::Right){
                    painting = true;
                    walling = false;
                }
            }
            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>()){   
                if (mouseButton->button == sf::Mouse::Button::Left){
                    painting = false;
                }
                if (mouseButton->button == sf::Mouse::Button::Right){
                    painting = false;
                }
            }
        }

       
    
        // Rendering State
        window.clear(sf::Color(30, 30, 40)); 

        if (isSearching){
            painting = false;
            Cell* cell = pq.top();
            pq.pop();
            
            if (cell->row-1 >= 0 && grid[cell->row-1][cell->col].state != cellState::visited && grid[cell->row-1][cell->col].state != cellState::wall){
                grid[cell->row-1][cell->col].state = cellState::visited;
                grid[cell->row-1][cell->col].distance = cell->distance+1;
                grid[cell->row-1][cell->col].parent = cell;
                pq.push(&grid[cell->row-1][cell->col]);
            }
            if (cell->row+1 < GRID_SIZE && grid[cell->row+1][cell->col].state != cellState::visited && grid[cell->row+1][cell->col].state != cellState::wall){
                grid[cell->row+1][cell->col].state = cellState::visited;
                grid[cell->row+1][cell->col].distance = cell->distance+1;
                grid[cell->row+1][cell->col].parent = cell;
                pq.push(&grid[cell->row+1][cell->col]);
            }
            if (cell->col-1 >= 0 && grid[cell->row][cell->col-1].state != cellState::visited && grid[cell->row][cell->col-1].state != cellState::wall){
                grid[cell->row][cell->col-1].state = cellState::visited;
                grid[cell->row][cell->col-1].distance = cell->distance+1;
                grid[cell->row][cell->col-1].parent = cell;
                pq.push(&grid[cell->row][cell->col-1]);
            }
            if (cell->col+1 < GRID_SIZE && grid[cell->row][cell->col+1].state != cellState::visited && grid[cell->row][cell->col+1].state != cellState::wall){
                grid[cell->row][cell->col+1].state = cellState::visited;
                grid[cell->row][cell->col+1].distance = cell->distance+1;
                grid[cell->row][cell->col+1].parent = cell;
                pq.push(&grid[cell->row][cell->col+1]);
            }
            if (pq.empty()) isSearching = false;
        }

        if (grid[lastEnd.first][lastEnd.second].state == cellState::visited){
            isSearching = false;
            root = &grid[lastEnd.first][lastEnd.second];
            pathing = true;
        }

        if (pathing){
            if (root != nullptr){
                root->state = cellState::path;
                root = root->parent;
            }else{
                pathing = false;
            }
        }

         
        if (painting){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int x = static_cast<int>((float)mousePos.x / CELL_SIZE);
            int y = static_cast<int>((float)mousePos.y / CELL_SIZE);
            if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE){
                if (starting){
                    if (grid[y][x].state != cellState::end){
                        grid[lastStart.first][lastStart.second].state = cellState::empty;
                        grid[y][x].state = cellState::start;
                        lastStart = {y, x};
                    }
                }else if (ending){
                    if (grid[y][x].state != cellState::start){
                        grid[lastEnd.first][lastEnd.second].state = cellState::empty;
                        grid[y][x].state = cellState::end;
                        lastEnd = {y, x};
                    }
                }else{
                    if (grid[y][x].state != cellState::end && grid[y][x].state != cellState::start){
                        if (walling) {
                            grid[y][x].state = cellState::wall;
                        }else{
                            grid[y][x].state = cellState::empty;
                        }
                    }
                }
            }
        }
        
        // (Everything we want to draw on screen goes right here)
        for (int r = 0; r < GRID_SIZE; r++){
            for (int c = 0; c < GRID_SIZE; c++){
                switch (grid[r][c].state){
                    case cellState::wall:
                        cellShape.setFillColor(sf::Color::White);break;
                    case cellState::empty:
                        cellShape.setFillColor(sf::Color::Black);break;
                    case cellState::start:
                        cellShape.setFillColor(sf::Color::Green);break;
                    case cellState::end:
                        cellShape.setFillColor(sf::Color::Red);break;
                    case cellState::visited:
                        cellShape.setFillColor(sf::Color::Yellow);break;
                    case cellState::path:
                        cellShape.setFillColor(sf::Color::Green);break;
                    default: break;
                }
                cellShape.setPosition(sf::Vector2f((float)c * CELL_SIZE, (float)r * CELL_SIZE));
                window.draw(cellShape);
            }
        }


        window.display();
    }
    return 0;
}