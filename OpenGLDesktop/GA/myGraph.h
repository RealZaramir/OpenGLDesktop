#pragma once
#include "myVec3d.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <bitset>
#include <algorithm>
using namespace std;

struct Node
{
	std::vector<Node *>edges;
	myVec3d data;
};

class myGraph
{
private:

	std::vector<Node> Nodes;
	myVec3d dataSpace;


public:
	myGraph();
	Node& operator[](int i);
	Node& at(int i);
	Node& back();
	Node& front();

	void setDataSpace(myVec3d v);
	myVec3d getDataSpace();

	int size();
	int numNodes();
	int numEdges();
	void addEdge(int a, int b);
	void addNode(myVec3d v);
	void addNode(Node n);

	void deleteEdge(int a, int b);
	void deleteNode(int a);
	void clear();

	bool isConnected(int a, int b);

	vector<myVec3d* > getConnectedData(int a);
	vector<Node*> getConnected(int a);
	vector<Node*> getNearestNodes(myVec3d pos, int k);	//k-nearest nabours
	vector<int> getNearestNodesIndex(myVec3d pos, int k);

	string toString();


	~myGraph();
};

