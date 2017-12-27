#include "myGraph.h"



myGraph::myGraph()
{

}

Node& myGraph::operator[](int i)
{
	if (Nodes.size() <= i) {
		perror("ERROR: Operator[] index out of bounds.");
		exit(0);
	}
	else return (Nodes[i]);
}

Node& myGraph::at(int i)
{
	if (Nodes.size() <= i) {
		perror("ERROR: at() index out of bounds.");
		exit(0);
	}
	else return (Nodes[i]);
}

Node & myGraph::back()
{
	return Nodes.back();
}

Node & myGraph::front()
{
	return Nodes.front();
}

void myGraph::setDataSpace(myVec3d v)
{
	dataSpace = v;
}

myVec3d myGraph::getDataSpace()
{
	return dataSpace;
}

int myGraph::size()
{
	return Nodes.size();
}

int myGraph::numNodes()
{
	return Nodes.size();
}

int myGraph::numEdges()
{
	int edgeSize = 0;
	for (int i = 0; i < Nodes.size(); i++)edgeSize += Nodes[i].edges.size();
	return edgeSize;
}

void myGraph::addEdge(int a, int b)
{	
	if (a != b && isConnected(a, b) == false) {
		Nodes[a].edges.push_back(&Nodes[b]);
		Nodes[b].edges.push_back(&Nodes[a]);
	}
}

void myGraph::addNode(myVec3d v)
{
	Node n;

	n.data = v;			//data is added but not edges!!!!!!!!



	Nodes.push_back(n);
}

void myGraph::addNode(Node n)
{
	Nodes.push_back(n);
}

void myGraph::deleteEdge(int a, int b)
{
	if (a != b) {
		vector<Node *> *e = &Nodes[a].edges;
		Node *x = &Nodes[b];
		for (int j = 0; j < 2; j++){
			for (int i = 0; i < e->size(); i++) {
				if (e->at(i) == x) {
					e->erase(e->begin() + i);
					e = &(x->edges);
					x = &Nodes[a];
					i = 0;
					break;
				}
			}
		} 
	}

	/*
	if (a != b) {
		for (int i = 0; i < Nodes[a].edges.size(); i++) {
			if ((Nodes[a].edges[i]) == &Nodes[b]) {
				Nodes[a].edges.erase(Nodes[a].edges.begin() + i);
				break;
			}
		}

		for (int i = 0; i < Nodes[b].edges.size(); i++) {
			if ((Nodes[b].edges[i]) == &Nodes[a]) {
				Nodes[b].edges.erase(Nodes[b].edges.begin() + i);
				break;
			}
		}
	}
	*/

}

void myGraph::deleteNode(int a)
{
	if (a >= Nodes.size()) { cout << "ERROR: deleteNode index out of range!"; exit(1); }

	Node  *x = &Nodes[a];
	vector<Node *> *e;
	for (int i = 0; i < Nodes[a].edges.size(); i++) {
		e = &(Nodes[a].edges[i]->edges);

		for (int j = 0; j < e->size(); j++)if ( e->at(j) == x)e->erase(e->begin() + j);
	}
	Nodes.erase(Nodes.begin() + a);
}

void myGraph::clear()
{
	Nodes.clear();
}

bool myGraph::isConnected(int a, int b)
{
	if (a >= Nodes.size() || b >= Nodes.size()) { cout << "ERROR: isConnected index out of range!"; exit(1); }

	vector<Node *> &e = Nodes[b].edges;
	if (e.empty())return false;

	Node & x = Nodes[a];

	for (int i = 0; i < e.size(); i++)if (e[i] == &x)return true;
	return false;

	/*
	vector<Node *>::iterator it = std::find_if(e.begin(), e.end(), [x](Node * n) -> bool { return n == &x; });
	
	cout << &x << " = " << x.data.toString() << endl;
	for (int i = 0; i < e.size(); i++)cout << e[i] << " = " << e[i]->data.toString();

	if (e.end() == it)return false;
	else return true;
	*/
}

vector<myVec3d *> myGraph::getConnectedData(int a)
{
	vector<myVec3d *> arr;
	for (int i = 0; i < Nodes[a].edges.size(); i++)arr.push_back(&(Nodes[a].edges[i]->data));
	return arr;
}

vector<Node*> myGraph::getConnected(int a)
{
	return Nodes[a].edges;
}

vector<Node*> myGraph::getNearestNodes(myVec3d pos, int numConnections)
{
	//belong to k-nearest
	int lastIndex = Nodes.size() -1 ;
	float minDist, comp, worstBestDist;
	vector<Node*>list;
	Node* best;

	worstBestDist = 0; 		//init worstBest with value 0
	//try to connect with nearest nods "numConnections" times
	for (int j = 0; j < numConnections; j++) {

		minDist = LONG_MAX; 		//init minDist with MAX value

		//  go through all nodes (exapt for last because this is the current one)
		for (int k = 0; k < lastIndex; k++) {

			comp = Nodes[k].data.dist(Nodes.back().data);	//set comp to smallest dist to current node

			//set bestIndex to current index k and minDist to comp if new dist is smaller then the best old one and it is biller then the last best one
			if (comp < minDist && comp > worstBestDist) {
				best = &Nodes[k];
				minDist = comp;
			}
		}

		if (minDist != LONG_MAX) {
			list.push_back(best);
			worstBestDist = minDist;
		}
	}

	return list;
}

vector<int> myGraph::getNearestNodesIndex(myVec3d pos, int numConnections)
{
	//belong to k-nearest
	int lastIndex = Nodes.size() - 1;
	float minDist, comp, worstBestDist;
	vector<int> list;
	int best;

	worstBestDist = 0; 		//init worstBest with value 0
							//try to connect with nearest nods "numConnections" times
	for (int j = 0; j < numConnections; j++) {

		minDist = LONG_MAX; 		//init minDist with MAX value

									//  go through all nodes (exapt for last because this is the current one)
		for (int k = 0; k < lastIndex; k++) {

			comp = Nodes[k].data.dist(Nodes.back().data);	//set comp to smallest dist to current node

															//set bestIndex to current index k and minDist to comp if new dist is smaller then the best old one and it is biller then the last best one
			if (comp < minDist && comp > worstBestDist) {
				best = k;
				minDist = comp;
			}
		}

		if (minDist != LONG_MAX) {
			list.push_back(best);
			worstBestDist = minDist;
		}
	}

	return list;
}

string myGraph::toString()
{
	stringstream s;
	for (int i = 0; i < Nodes.size(); i++) {
		s << i << ") " << Nodes[i].data.toString() << ", NumEdges: " << Nodes[i].edges.size() << endl;
	}
	s << "NumNodes: " << numNodes() << ", numEdges: " << numEdges() << endl;
	return s.str();
}




myGraph::~myGraph()
{
}
