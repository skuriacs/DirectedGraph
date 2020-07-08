#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Node
{
	vector<Node*> adjacentNodes;
	vector<int> weights;
	int name;
	Node(int name)
	{
		this->name = name;
	}
	int findNode(Node* nodeToFind)
	{
		for (int i = 0; i < adjacentNodes.size(); i++)
		{
			if (adjacentNodes[i] == nodeToFind)
				return i;
		}
		return -1;
	}
};
class Graph
{

public:
	void insertEdge(int from, int to, int weight);
	bool isEdge(int from, int to);
	int getWeight(int from, int to);
	vector<int> getAdjacent(int vertex);
	void printGraph();

private:
	vector<Node*> nodes;
};

void Graph::insertEdge(int from, int to, int weight)
{
	if (nodes.empty())
	{
		nodes.push_back(new Node(from));
		nodes.push_back(new Node(to));
		nodes[0]->adjacentNodes.push_back(nodes[1]);
		nodes[1]->adjacentNodes.push_back(nodes[0]);
		nodes[0]->weights.push_back(weight);
		nodes[1]->weights.push_back(-1);
	}
	else
	{
		Node* fromNode = nullptr, * toNode = nullptr;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->name == from)
				fromNode = nodes[i];
			if (nodes[i]->name == to)
				toNode = nodes[i];
		}
		if (fromNode == nullptr)
		{
			fromNode = new Node(from);
			nodes.push_back(fromNode);
		}
		if (toNode == nullptr)
		{
			toNode = new Node(to);
			nodes.push_back(toNode);
		}
		fromNode->adjacentNodes.push_back(toNode);
		toNode->adjacentNodes.push_back(fromNode);
		fromNode->weights.push_back(weight);
		toNode->weights.push_back(-1);
	}
}

bool Graph::isEdge(int from, int to)
{
	Node* fromNode = nullptr, * toNode = nullptr;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->name == from)
			fromNode = nodes[i];
		if (nodes[i]->name == to)
			toNode = nodes[i];
	}
	if (fromNode == nullptr || toNode == nullptr)
		return false;
	int found = fromNode->findNode(toNode);
	if (found == -1)
		return false;
	if (fromNode->weights[found] != -1)
		return true;
	return false;
}
int Graph::getWeight(int from, int to)
{
	Node* fromNode = nullptr, * toNode = nullptr;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->name == from)
			fromNode = nodes[i];
		if (nodes[i]->name == to)
			toNode = nodes[i];
	}
	int found = fromNode->findNode(toNode);
	return fromNode->weights[found];
}
void Graph::printGraph()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i]->name;
		for (int j = 0; j < nodes[i]->adjacentNodes.size(); j++)
		{
			if (nodes[i]->weights[j] != -1)
			{
				cout << " " << nodes[i]->adjacentNodes[j]->name;
			}
		}
		if(i < nodes.size() -1)
			cout << "\n";
	}
	
}
vector<int> Graph::getAdjacent(int vertex)
{
	Node* vertexNode = nullptr;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->name == vertex)
		{
			vertexNode = nodes[i];
			break;
		}
	}

	vector<int> adjacentVertices;
	if (vertexNode == nullptr)
		return adjacentVertices;
	for (int i = 0; i < vertexNode->adjacentNodes.size(); i++)
	{
		adjacentVertices.push_back(vertexNode->adjacentNodes[i]->name);
	}
	return adjacentVertices;
}
int main()
{
	//DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK

	int noOfLines, operation, vertex, to, fro, weight, source, j;
	vector<int> arr;
	int arrSize;
	Graph g;
	cin >> noOfLines;
	for (int i = 0; i < noOfLines; i++)
	{
		cin >> operation;
		switch (operation)
		{
		case 1:
			cin >> fro;
			cin >> to;
			cin >> weight;
			g.insertEdge(fro, to, weight);
			break;
		case 2:
			cin >> fro;
			cin >> to;
			cout << g.isEdge(fro, to) << "\n";
			break;
		case 3:
			cin >> fro;
			cin >> to;
			cout << g.getWeight(fro, to) << "\n";
			break;
		case 4:
			cin >> vertex;
			arr = g.getAdjacent(vertex);
			arrSize = arr.size();
			j = 0;
			while (j < arrSize)
			{
				cout << arr[j] << " ";
				j++;
			}
			cout << "\n";
			break;
		case 5:
			g.printGraph();
			cout << "\n";
			break;
		}
	}
}