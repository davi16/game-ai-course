#include "Cell.h"

Cell::Cell(int r, int c, int clr, Cell* p)
{
	row = r;
	col = c;
	color = clr;
	parent = p;
}