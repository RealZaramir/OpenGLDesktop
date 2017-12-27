#pragma once

#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include "myGraph.h"


using namespace std;

struct Spine
{
	vector<myVec3d>joints;
};

class Structure
{

private:
	int size;
	float fitness;
	myGraph genotype;
	myVec3d creationSpace;

	void mutateMove(float rate, float threshold);
	void mutateAdd(float rate);
	void mutateRemove(float rate);

public:
	Structure();
	Structure(int s);

	void setSize(int s);
	int getSize();
	void setCreationSpace(myVec3d v);
	myVec3d getCreationSpace();
	float getFitness();

	void randomStructure(int w, int d, int h);
	void randomStructure();	//uses the creationSpace as boundery

	void buildStructure(vector<Spine> skeleton, int numPoints, int numConnections, int threshold);	//bild structure from skeleton (spines)

	void calcFitness();
	void mutate(float rate_move, float rate_add, float rate_remove);

	Structure crossover(Structure * other);
	void crossover(Structure **parent, Structure *kid1, Structure *kid2);

	vector<float> getNodeData();

	string toString();

	~Structure();
};

