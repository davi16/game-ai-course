#define GL_SILENCE_DEPRECATION
#include <stdlib.h>
#include <time.h>
#include "glut.h"
#include "Maze.h"

Maze gameMaze;

void init()
{
	glClearColor(0.5, 0.5, 0.5, 0);
	glOrtho(0, MSZ, 0, MSZ, -1, 1);

	srand((unsigned int)time(0));
	gameMaze.Init();
}

void DrawMaze()
{
	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
		{
			switch (gameMaze.GetCellColor(i, j))
			{
			case WALL:
				glColor3d(0.4, 0, 0);
				break;
			case SPACE:
				glColor3d(0.8, 0.8, 0.8);
				break;
			case START:
				glColor3d(0.5, 0.8, 1);
				break;
			case TARGET:
				glColor3d(1, 0, 0);
				break;
			case BLACK:
				glColor3d(0.4, 0.4, 0.4);
				break;
			case GRAY:
				glColor3d(0, 1, 0);
				break;
			case TARGET_BLACK:
				glColor3d(0.3, 0.3, 0.5);
				break;
			case TARGET_GRAY:
				glColor3d(0, 0.8, 0.8);
				break;
			case PATH:
				glColor3d(1, 1, 0);
				break;
			}

			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i + 1);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j + 1, i);
			glEnd();
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawMaze();
	glutSwapBuffers();
}

void idle()
{
	if (gameMaze.IsRunning())
	{
		gameMaze.BidirectionalBFSIteration();
	}
	glutPostRedisplay();
}

void menu(int choice)
{
	switch (choice)
	{
	case 1:
		gameMaze.StartBidirectionalBFS();
		break;
	case 2:
		gameMaze.ResetSameMaze();
		break;
	case 3:
		gameMaze.Init();
		break;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Bidirectional BFS");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutCreateMenu(menu);
	glutAddMenuEntry("Bidirectional BFS", 1);
	glutAddMenuEntry("Reset Same Maze", 2);
	glutAddMenuEntry("New Random Maze", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutMainLoop();
	return 0;
}