#include "Maze.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Maze::Maze()
{
	isRunning = false;
	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
		{
			grid[i][j] = SPACE;
			initialGrid[i][j] = SPACE;
			startCells[i][j] = nullptr;
			targetCells[i][j] = nullptr;
		}
	}
}

void Maze::ClearSearchState()
{
	while (!startGrays.empty()) startGrays.pop();
	while (!targetGrays.empty()) targetGrays.pop();
	isRunning = false;

	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
		{
			startCells[i][j] = nullptr;
			targetCells[i][j] = nullptr;
		}
	}
}

void Maze::ResetSameMaze()
{
	ClearSearchState();

	int startR = -1, startC = -1;
	int targetR = -1, targetC = -1;

	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
		{
			grid[i][j] = initialGrid[i][j];
			if (grid[i][j] == START)
			{
				startR = i;
				startC = j;
			}
			else if (grid[i][j] == TARGET)
			{
				targetR = i;
				targetC = j;
			}
		}
	}

	if (startR != -1 && startC != -1)
	{
		Cell* pStart = new Cell(startR, startC, START, nullptr);
		startGrays.push(pStart);
		startCells[startR][startC] = pStart;
	}

	if (targetR != -1 && targetC != -1)
	{
		Cell* pTarget = new Cell(targetR, targetC, TARGET, nullptr);
		targetGrays.push(pTarget);
		targetCells[targetR][targetC] = pTarget;
	}
}

void Maze::Init()
{
	int i, j;
	ClearSearchState();

	for (i = 0; i < MSZ; i++)
	{
		grid[0][i] = WALL;
		grid[MSZ - 1][i] = WALL;
		grid[i][0] = WALL;
		grid[i][MSZ - 1] = WALL;
	}

	for (i = 1; i < MSZ - 1; i++)
	{
		for (j = 1; j < MSZ - 1; j++)
		{
			if (i % 2 == 0)
			{
				if (rand() % 100 < 80) grid[i][j] = SPACE;
				else grid[i][j] = WALL;
			}
			else
			{
				if (rand() % 100 < 35) grid[i][j] = SPACE;
				else grid[i][j] = WALL;
			}
		}
	}

	int startR = MSZ / 2;
	int startC = MSZ / 2;
	int targetR = 1 + rand() % (MSZ - 2);
	int targetC = 1 + rand() % (MSZ - 2);

	grid[startR][startC] = START;
	grid[targetR][targetC] = TARGET;

	// save the initial maze configuration for resetting later
	for (i = 0; i < MSZ; i++)
	{
		for (j = 0; j < MSZ; j++)
		{
			initialGrid[i][j] = grid[i][j];
		}
	}

	Cell* pStart = new Cell(startR, startC, START, nullptr);
	startGrays.push(pStart);
	startCells[startR][startC] = pStart;

	Cell* pTarget = new Cell(targetR, targetC, TARGET, nullptr);
	targetGrays.push(pTarget);
	targetCells[targetR][targetC] = pTarget;
}

void Maze::RestoreSingleDirection(Cell* p, int stopColor)
{
	while (p != nullptr && p->getColor() != stopColor)
	{
		p->setColor(PATH);
		grid[p->getRow()][p->getCol()] = PATH;
		p = p->getParent();
	}
}

void Maze::RestoreBothPaths(Cell* meetingFromStart, Cell* meetingFromTarget)
{
	RestoreSingleDirection(meetingFromStart, START);
	RestoreSingleDirection(meetingFromTarget, TARGET);
}

bool Maze::CheckStartNeighbor(int row, int col, Cell* pCurrent)
{
	if (grid[row][col] == TARGET || grid[row][col] == TARGET_GRAY || grid[row][col] == TARGET_BLACK)
	{
		cout << "The solution has been found! Searches met at (" << row << ", " << col << ")\n";
		isRunning = false;
		RestoreBothPaths(pCurrent, targetCells[row][col]);
		return false;
	}
	else
	{
		Cell* pn = new Cell(row, col, GRAY, pCurrent);
		grid[row][col] = GRAY;
		startCells[row][col] = pn;
		startGrays.push(pn);
		return true;
	}
}

bool Maze::CheckTargetNeighbor(int row, int col, Cell* pCurrent)
{
	if (grid[row][col] == START || grid[row][col] == GRAY || grid[row][col] == BLACK)
	{
		cout << "The solution has been found! Searches met at (" << row << ", " << col << ")\n";
		isRunning = false;
		RestoreBothPaths(startCells[row][col], pCurrent);
		return false;
	}
	else
	{
		Cell* pn = new Cell(row, col, TARGET_GRAY, pCurrent);
		grid[row][col] = TARGET_GRAY;
		targetCells[row][col] = pn;
		targetGrays.push(pn);
		return true;
	}
}

void Maze::StepFromStart()
{
	Cell* pCurrent = startGrays.front();
	startGrays.pop();

	int row = pCurrent->getRow();
	int col = pCurrent->getCol();

	if (pCurrent->getColor() != START)
	{
		grid[row][col] = BLACK;
		pCurrent->setColor(BLACK);
	}

	bool go_on = true;
	int dRow[] = { 1, -1, 0, 0 };
	int dCol[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4 && go_on; i++)
	{
		int nr = row + dRow[i];
		int nc = col + dCol[i];
		int cellVal = grid[nr][nc];

		if (cellVal == SPACE || cellVal == TARGET || cellVal == TARGET_GRAY || cellVal == TARGET_BLACK)
		{
			go_on = CheckStartNeighbor(nr, nc, pCurrent);
		}
	}
}

void Maze::StepFromTarget()
{
	Cell* pCurrent = targetGrays.front();
	targetGrays.pop();

	int row = pCurrent->getRow();
	int col = pCurrent->getCol();

	if (pCurrent->getColor() != TARGET)
	{
		grid[row][col] = TARGET_BLACK;
		pCurrent->setColor(TARGET_BLACK);
	}

	bool go_on = true;
	int dRow[] = { 1, -1, 0, 0 };
	int dCol[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4 && go_on; i++)
	{
		int nr = row + dRow[i];
		int nc = col + dCol[i];
		int cellVal = grid[nr][nc];

		if (cellVal == SPACE || cellVal == START || cellVal == GRAY || cellVal == BLACK)
		{
			go_on = CheckTargetNeighbor(nr, nc, pCurrent);
		}
	}
}

void Maze::BidirectionalBFSIteration()
{
	if (!isRunning) return;

	if (startGrays.empty() || targetGrays.empty())
	{
		cout << "There is no solution\n";
		isRunning = false;
		return;
	}

	StepFromStart();

	if (isRunning && !targetGrays.empty())
	{
		StepFromTarget();
	}
}