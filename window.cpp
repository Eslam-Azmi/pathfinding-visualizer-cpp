#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

enum class cellState{
    empty,
    wall,
    start,
    end
};

struct Cell{
    int row;
    int col;
    cellState state = cellState::empty;
};

int main() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 800;
    
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "A* & Dijkstra Pathfinding Visualizer");
    
    window.setFramerateLimit(60);

    const int GRID_SIZE = 40;
    const float CELL_SIZE = 20.0f;

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

    pair<int,int> lastStart = {GRID_SIZE-1,GRID_SIZE-1};
    grid[GRID_SIZE-1][GRID_SIZE-1].state = cellState::start;
    pair<int,int> lastEnd = {0,0};
    grid[0][0].state = cellState::end;

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
                        }
                    }
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

        // 4. Updating Logic (We will put grid updates here later)
    
        // 5. Rendering State
        window.clear(sf::Color(30, 30, 40)); // A nice dark background matching your VS Code theme

        if (painting){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int x = static_cast<int>((float)mousePos.x / CELL_SIZE);
            int y = static_cast<int>((float)mousePos.y / CELL_SIZE);
            if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE){
                if (starting){
                    grid[lastStart.first][lastStart.second].state = cellState::empty;
                    grid[y][x].state = cellState::start;
                    lastStart = {y, x};
                }else if (ending){
                    grid[lastEnd.first][lastEnd.second].state = cellState::empty;
                    grid[y][x].state = cellState::end;
                    lastEnd = {y, x};
                }else{
                    if (walling) {
                        grid[y][x].state = cellState::wall;
                    }else{
                        grid[y][x].state = cellState::empty;
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
                    default: break;
                }



                // if (grid[r][c].state == cellState::wall){
                //     cellShape.setFillColor(sf::Color::White);
                // }else if (grid[r][c].state == cellState::empty){
                //     cellShape.setFillColor(sf::Color::Black);
                // }else{
                //     cellShape.setFillColor(sf::Color::Green);
                // }
                cellShape.setPosition(sf::Vector2f((float)c * CELL_SIZE, (float)r * CELL_SIZE));
                window.draw(cellShape);
            }
        }


        window.display();
    }
    return 0;
}