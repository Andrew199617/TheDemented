#pragma once
#include "AsciiFormats.h"
#include <windows.h>
#include <vector>
using std::vector;

class Node
{
public:
	Node();
	~Node();

	int x;
	int y;

	bool visited;

	vector<Node*> AdjacentNodes;

	WORD color;
	AsciiFormats format;

	void SetValue();
};

