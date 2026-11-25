# Game AI – Course Assignments & Final Project

This repository tracks coursework assignments and the final project for the **Game Artificial Intelligence** course.

## Repository Structure

```text
.
├── .gitignore
├── README.md
└── hw2-bidirectional-bfs/
    ├── Cell.h
    ├── Cell.cpp
    ├── Maze.h
    ├── Maze.cpp
    └── main.cpp

## Homework 2: Bidirectional BFS Search
### Overview
```text
Implementation of Bidirectional BFS on a 2D grid maze: two breadth-first searches run in parallel—one starting from START and the other from TARGET—until their frontiers meet, and then reconstruct the shortest path between them.   

### Architecture & Design (SOLID)
```text
Cell.h / Cell.cpp – Represents a single grid cell (row, column, color/state, and parent pointer).   

Maze.h / Maze.cpp – Encapsulates maze initialization, resetting the exact same maze (ResetSameMaze), managing both search queues, executing bidirectional BFS steps, and reconstructing the path.
main.cpp – Handles rendering and user interaction via OpenGL and GLUT (display, idle, and right-click context menu).

### Build & Run
**macOS (Terminal / VS Code)**

```bash
g++ hw2-bidirectional-bfs/*.cpp -o app -framework OpenGL -framework GLUT
./app

### Windows (Visual Studio)
Open the project file in Visual Studio and build from the IDE.

### Controls (Right-Click Menu)
**Bidirectional BFS –** Start running bidirectional search.   
**Reset Same Maze –** Reset search state on the current maze to replay/demonstrate the same run.
**New Random Maze –** Generate a new random maze.

## Upcoming Assignments & Final Project
**HW3: (To be added)**
**Final Project: (To be added)**