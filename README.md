# 🚀 Interactive C++ Pathfinding Visualizer

A high-performance, interactive 2D grid simulation built from scratch in C++ using the SFML graphics library. This project visually demonstrates how classic graph theory algorithms (Dijkstra's and A*) navigate obstacles to compute the absolute shortest path between two nodes in real-time.

Built with a strong emphasis on clean code structure, memory-safe data structures, and efficient state management.

---

## 🎮 Features & Core Mechanics

* **Interactive Grid Map Editor:** A fully dynamic 40x40 grid canvas with real-time mouse tracking and boundary protection.
* **Dual-Button Control Scheme:** Left-click to paint solid walls; right-click to erase them smoothly.
* **Dynamic Anchor Placement:** Hold `S` + click to set/drag the Start Node (Green), or hold `E` + click to set/drag the Target Node (Red) with strict mutual exclusion logic.
* **Instant Map Clearance:** Press `R` to reset the entire grid state instantaneously.
* **Optimized Rendering Pipeline:** Custom state-based switch rendering utilizing inward outline adjustments (-0.5f thickness math) for perfect layout alignment.

## 🛠️ Built With

* **Language:** C++17 / C++20
* **Graphics & Windowing:** SFML (Simple and Fast Multimedia Library)
* **Memory Architecture:** Bounded 2D Standard Vectors (`std::vector<std::vector<Cell>>`) and `std::pair` tracking containers.
