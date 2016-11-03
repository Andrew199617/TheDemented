#pragma once
#include "Node.h"
#include <vector>
#include "XY.h"
#include "MazeData.h"

using std::vector;

class GenerateMaze
{
public:
	GenerateMaze() {}
	GenerateMaze(int width, int height);
	~GenerateMaze();

	void Initialize(int width, int height);
	MazeData* GetMazeData();
	void DepthFirstGeneration();
	void ChoseExit();
	void CheckAdjacentIteratively();
	bool HasAdjacent(XY xy);


private:
	void SetNodeToAdd(int, int);

public:
	Node nodes[100][100];
	vector<XY> currentlyVisiting;
	vector<XY> exitPath;
	unsigned exitNodeSize;
	XY exitNode;

private:
	MazeData* mazeData;
	int m_Width;
	int m_Height;
	XY startNode;
	int NextPossibleNodes[4][2];
};

