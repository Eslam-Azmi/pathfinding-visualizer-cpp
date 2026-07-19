#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/Pathfinding.hpp"
#include "../include/Grid.hpp"
using namespace std;

pair<int,int> lastStart = {-1,-1};
pair<int,int> lastEnd = {-1,-1};

int main(){
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 800;


    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "A* & Dijkstra Pathfinding Visualizer");
    window.setFramerateLimit(30);

    Grid grid(20,40.0f);
    Pathfinding pathfinder;

    while(window.isOpen()){
        while (const optional<sf::Event> event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }

                if (keyPressed->code == sf::Keyboard::Key::R) {
                    pathfinder.reset();
                    grid.hardReset(lastStart, lastEnd);
                }
                if (keyPressed->code == sf::Keyboard::Key::C) {
                    pathfinder.reset();
                    grid.softClear(lastStart, lastEnd);
                }

                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    if (lastStart.first != -1 && lastEnd.first != -1) {
                        pathfinder.startSearch(grid, lastStart, lastEnd);
                    } else {
                        cout << "Error: You must place both a Start (S) and End (E) node!" << endl;
                    }
                }
            }
        }

        if (!pathfinder.isRunning()){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                    grid.handlePainting(window, true, false, false, lastStart, lastEnd);
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)){
                    grid.handlePainting(window, false, true, false, lastStart, lastEnd);
                }else{
                    grid.handlePainting(window, false, false, true, lastStart, lastEnd);
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                grid.handlePainting(window, false, false, false, lastStart, lastEnd);
            }
        }

        if (pathfinder.isRunning() && !pathfinder.isPathFound()){
            pathfinder.step(grid);
        }else if (pathfinder.isPathFound()){
            pathfinder.pathing(grid);
        }

        window.clear();

        grid.draw(window);

        window.display();
    }

    return 0;
}


