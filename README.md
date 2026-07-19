# 🚀 Interactive C++ Pathfinding Visualizer

A high-performance, interactive 2D grid simulation built from scratch in C++ using the SFML graphics library. This project visually demonstrates how classic graph theory algorithms navigate obstacles to compute the absolute shortest path between two nodes in real-time.

Built with a strong emphasis on clean multi-file architecture (`src/` and `include/`), memory-safe data structures, and frame-by-frame state animation.

---

## 🎮 Features & Core Mechanics

* **Interactive Grid Map Editor:** A dynamic 20x20 grid canvas optimized for an 800x800 viewport with real-time mouse tracking and boundary protection.
* **Dual-Button Control Scheme:** Left-click and drag to paint solid walls; right-click and drag to erase them smoothly.
* **Dynamic Anchor Placement:** Hold `S` + Left-Click to place/drag the Start Node (Green), or hold `E` + Left-Click to place/drag the Target Node (Red) with auto-overwriting exclusion logic.
* **Frame-by-Frame Visual Animation:** Both the search wave expansion and the final shortest path reconstruction are animated step-by-step across successive frames instead of snapping instantly.
* **Dual Reset Modes:** Press `R` for a hard reset (wipes everything) or press `C` for a soft clear (erases path visual animations while preserving your custom wall layouts).

## 🛠️ Built With

* **Language:** C++20 Standard
* **Graphics & Windowing:** SFML 3 (Simple and Fast Multimedia Library)
* **Architecture:** Structured multi-file layout separating declarations (`include/`) from definitions (`src/`).
* **Memory Containers:** Custom 2D standard vectors (`std::vector<std::vector<Cell>>`) managed by pointer-based address tracking via an optimized `std::priority_queue`.
