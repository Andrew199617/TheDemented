#pragma once
#include "TheDemented.h"
#include "Node.h"
#include "XY.h"

class MazeData
{
public:
	MazeData() {}
	~MazeData() {}

	Node nodes[100][100];
	XY exitNode;
	int m_Width;
	int m_Height;
	XY startNode;
};
