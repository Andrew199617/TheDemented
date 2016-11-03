
#include "TheDemented.h"
#include "Node.h"

Node::Node()
{
	visited = false;
	format = AsciiFormats::Empty;
}


Node::~Node()
{
}

void Node::SetValue()
{
	for (unsigned i = 0; i < AdjacentNodes.size(); i++)
	{
		if (AdjacentNodes.at(i)->x > x)
		{
			format = AsciiFormats(format + AsciiFormats::HasRight);
		}
		else if (AdjacentNodes.at(i)->x < x)
		{
			format = AsciiFormats(format + AsciiFormats::HasLeft);
		}
		else if (AdjacentNodes.at(i)->y < y)
		{
			format = AsciiFormats(format + AsciiFormats::HasTop);
		}
		else if (AdjacentNodes.at(i)->y > y)
		{
			format = AsciiFormats(format + AsciiFormats::HasBot);
		}
	}
	
}
