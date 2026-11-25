#pragma once
#include <queue>
#include "Cell.h"

const int MSZ = 100;

const int SPACE = 0;
const int WALL = 1;
const int START = 2;
const int TARGET = 3;
const int BLACK = 4;
const int GRAY = 5;
const int PATH = 6;
const int TARGET_BLACK = 7;
const int TARGET_GRAY = 8;

class Maze
{
private:
	int grid[MSZ][MSZ];
	int initialGrid[MSZ][MSZ]; // copy of the initial maze, to allow resetting the search without regenerating the maze
	std::queue<Cell*> startGrays;
	std::queue<Cell*> targetGrays;

	Cell* startCells[MSZ][MSZ];
	Cell* targetCells[MSZ][MSZ];

	bool isRunning;

	void ClearSearchState();
	void RestoreBothPaths(Cell* meetingFromStart, Cell* meetingFromTarget);
	void RestoreSingleDirection(Cell* p, int stopColor);
	bool CheckStartNeighbor(int row, int col, Cell* pCurrent);
	bool CheckTargetNeighbor(int row, int col, Cell* pCurrent);
	void StepFromStart();
	void StepFromTarget();

public:
	Maze();
	void Init();
	void ResetSameMaze();
	void StartBidirectionalBFS() { isRunning = true; }
	bool IsRunning() const { return isRunning; }
	void BidirectionalBFSIteration();
	int GetCellColor(int row, int col) const { return grid[row][col]; }
};