# 🚀 Interactive C++ Pathfinding Visualizer

A high-performance, interactive 2D grid simulation built from scratch in C++ using the SFML graphics library. This project visually demonstrates how classic graph theory algorithms (**A*** and **Dijkstra**) navigate obstacles and weighted terrain to compute the absolute shortest path between two nodes in real-time.

Built with a strong emphasis on clean multi-file architecture (`src/` and `include/`), memory-safe data structures, and frame-by-frame state animation.

---

## 🎮 Features & Core Mechanics

* **Interactive Grid Map Editor:** A dynamic 20x20 grid canvas optimized for an 800x800 viewport with real-time mouse tracking and boundary protection.
* **Weighted Terrain System:** Paint custom terrain tiles like **Mud** that carry higher step costs, forcing $A^*$ to evaluate whether bypassing terrain is more efficient than cutting through it.
* **Dynamic Anchor Placement:** Hold `S` + Left-Click to place/drag the Start Node (Green), or hold `E` + Left-Click to place/drag the Target Node (Red) with auto-overwriting exclusion logic.
* **Frame-by-Frame Animation:** Both the search wave expansion and the final shortest path reconstruction are animated step-by-step across successive frames.
* **Dual Reset Modes:** Press `R` for a hard reset (wipes the entire grid) or press `C` for a soft clear (erases visited/path visuals while preserving your custom wall and mud layouts).

---

## ⌨️ Controls

| Key / Input | Action |
| :--- | :--- |
| **Left Click + Drag** | Draw solid Walls |
| **Right Click + Drag** | Erase Walls or Mud |
| **Hold `S` + Left Click** | Set Start Node (Green) |
| **Hold `E` + Left Click** | Set Target Node (Red) |
| **Hold `M` + Left Click** | Paint Mud Terrain (Brown) |
| **`Enter`** | Run Pathfinding Algorithm |
| **`C`** | Clear Path (keep walls and mud) |
| **`R`** | Reset Grid completely |
| **`Esc`** | Exit Application |

---

## 🛠️ Built With

* **Language:** C++20 Standard
* **Graphics & Windowing:** SFML 3 (Simple and Fast Multimedia Library)
* **Architecture:** Structured multi-file layout separating declarations (`include/`) from definitions (`src/`).
* **Memory Containers:** Custom 2D standard vectors (`std::vector<std::vector<Cell>>`) managed by pointer-based address tracking via an optimized min-heap `std::priority_queue`.
