
#include "TheDemented.h"
#include "GenerateMaze.h"
#include <cstdlib>
#include <vector>
#include <time.h>
#include <iostream>
#include "MazeData.h"

using std::vector;

GenerateMaze::GenerateMaze(int width, int height)
{
	Initialize(width, height);
}


GenerateMaze::~GenerateMaze()
{
	/*for (int i = 0; i < m_Width; i++)
	{
		delete[] nodes[i];
	}
	delete[] nodes;*/
}

void GenerateMaze::Initialize(int width, int height)
{
	exitNodeSize = 0;
	m_Width = width;
	m_Height = height;
	
	DepthFirstGeneration();
}

MazeData* GenerateMaze::GetMazeData()
{
	mazeData = new MazeData;
	mazeData->exitNode = exitNode;
	mazeData->m_Height = m_Height;
	mazeData->m_Width = m_Width;
	mazeData->startNode = startNode;
	for (int i = 0; i < m_Height; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			mazeData->nodes[j][i] = nodes[j][i];
		}
	}
	return mazeData;
}

void GenerateMaze::DepthFirstGeneration()
{
	//top or bottom
	srand(time(NULL));
	int startX = rand() % m_Width;
	int startY = (rand() % 2) * m_Height;
	if (startY == m_Height)
	{
		startY--;
	}
	nodes[startX][startY].x = startX;
	nodes[startX][startY].y = startY;
	nodes[startX][startY].visited = true;
	SetNodeToAdd(startX, startY);
	currentlyVisiting.push_back(startNode);
	
	CheckAdjacentIteratively();

	for (int i = 0; i < m_Height; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			nodes[j][i].SetValue();
		}
	}
}

void GenerateMaze::CheckAdjacentIteratively()
{
	XY xy;
	for (int i = 1; i < m_Width * m_Height; i++)
	{
		int curNode[2] = { currentlyVisiting.back().x,currentlyVisiting.back().y };
		int x = curNode[0];
		int y = curNode[1];

		int numNodes = 0;

		if (x > 0 && !nodes[x - 1][y].visited)
		{
			NextPossibleNodes[numNodes][0] = x - 1;
			NextPossibleNodes[numNodes][1] = y;
			numNodes++;
		}

		if (y > 0 && !nodes[x][y - 1].visited)
		{
			NextPossibleNodes[numNodes][0] = x;
			NextPossibleNodes[numNodes][1] = y - 1;
			numNodes++;
		}

		if (x < m_Width - 1 && !nodes[x + 1][y].visited)
		{
			NextPossibleNodes[numNodes][0] = x + 1;
			NextPossibleNodes[numNodes][1] = y;
			numNodes++;
		}

		if (y < m_Height - 1 && !nodes[x][y + 1].visited)
		{
			NextPossibleNodes[numNodes][0] = x;
			NextPossibleNodes[numNodes][1] = y + 1;
			numNodes++;
		}

		if (numNodes == 0)
		{
			if (currentlyVisiting.size() > exitNodeSize)
			{
				exitNodeSize = currentlyVisiting.size();
				exitNode = currentlyVisiting.back();
				exitPath = currentlyVisiting;
				
			}
			currentlyVisiting.pop_back();
			while (!HasAdjacent(currentlyVisiting.back()))
			{
				currentlyVisiting.pop_back();
				if (currentlyVisiting.empty())
				{
					return;
				}
			}
			i--;
			continue;
		}

		int nextAdjacent = rand() % numNodes;
		curNode[0] = NextPossibleNodes[nextAdjacent][0];
		curNode[1] = NextPossibleNodes[nextAdjacent][1];
		Node* node = &nodes[curNode[0]][curNode[1]];
		node->AdjacentNodes.push_back(&nodes[x][y]);
		node->x = curNode[0];
		node->y = curNode[1];
		node->visited = true;
		node->color = 0x2B;
		nodes[x][y].AdjacentNodes.push_back(node);
		xy.x = NextPossibleNodes[nextAdjacent][0];
		xy.y = NextPossibleNodes[nextAdjacent][1];
		currentlyVisiting.push_back(xy);
	}
}

bool GenerateMaze::HasAdjacent(XY xy)
{
	int x = xy.x;
	int y = xy.y;

	if (x > 0 && !nodes[x - 1][y].visited)
	{
		return true;
	}
	if (y > 0 && !nodes[x][y - 1].visited)
	{
		return true;
	}
	if (x < m_Width - 1 && !nodes[x + 1][y].visited)
	{
		return true;
	}
	if (y < m_Height - 1 && !nodes[x][y + 1].visited)
	{
		return true;
	}
	return false;
}

void GenerateMaze::SetNodeToAdd(int x, int y)
{
	startNode.x = x;
	startNode.y = y;
}
