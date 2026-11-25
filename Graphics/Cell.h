#pragma once

class Cell
{
	private:
		int row, col;
		int color;
		Cell* parent;
	public:
		Cell(int r, int c, int clr, Cell* p);
		int getRow() { return row; }
		int getCol() { return col; }
		int getColor() { return color; }
		Cell* getParent() { return parent; }
		void setColor(int c) { color = c; }
		void setParent(Cell* p) { parent = p; }
};

