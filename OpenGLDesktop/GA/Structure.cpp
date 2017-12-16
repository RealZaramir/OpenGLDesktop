#include "Structure.h"


void Structure::mutateMove(float rate, float threshold)
{
	int rand0to1 = 0;
	myVec3d vec;

	for (int i = 0; i < genotype.numNodes(); i++) {
		rand0to1 = rand() % 100;
		if (rand0to1 < rate * 100) {
			vec.setRandom(-threshold, threshold);
			vec += genotype[i].data;
			
			if (vec.inBox(creationSpace))genotype[i].data.set(vec);
		}
	}
}

void Structure::mutateAdd(float rate)
{
	float rand0to1 = 0;
	float threshold = 100;
	vector<int> nearest;
	myVec3d vec;
	for (int i = 0; i < genotype.numNodes(); i++) {
		rand0to1 = rand() % 100;
		if (rand0to1 < rate * 100) {
			vec.setRandomByMag(threshold);
			vec += genotype[rand() % genotype.numNodes()].data;
			genotype.addNode(vec);
			nearest = genotype.getNearestNodesIndex(vec, 3);
			for (int j = 0; j < nearest.size(); j++) genotype.addEdge(genotype.numNodes() - 1, nearest[j]);
			size++;
		}
	}
}

void Structure::mutateRemove(float rate)
{
	size = genotype.numNodes();
	float rand0to1 = 0;
	for (int i = 0; i < size; i++) {
		rand0to1 = rand() % 100;
		if (rand0to1 <= rate * 100) {
			genotype.deleteNode(i);
			size--;
		}
	}
	cout << genotype.numNodes() << " = " << size << endl;
}

Structure::Structure()
{
	size = 0;
	fitness = 0;
}

Structure::Structure(int s)
{
	size = s;
	fitness = 0;
}

void Structure::setSize(int s)
{
	size = s;
}

int Structure::getSize()
{
	size = genotype.size();
	return genotype.size();
}

void Structure::setCreationSpace(myVec3d v)
{
	creationSpace.set(v);
}

myVec3d Structure::getCreationSpace()
{
	return creationSpace;
}

float Structure::getFitness()
{
	return fitness;
}

void Structure::randomStructure(int w, int d, int h)
{
	creationSpace.setComp(w, d, h);
	for (int i = 0; i < size; i++)genotype.addNode(myVec3d(rand() % w, rand() % d, rand() % h));
}

void Structure::randomStructure()
{
	for (int i = 0; i < size; i++)genotype.addNode(myVec3d(rand() % (int)creationSpace.x, rand() % (int)creationSpace.y, rand() % (int)creationSpace.z));
}

void Structure::buildStructure(vector<Spine> skeleton, int numPoints, int numConnections, int threshold)
{
	size = numPoints;
	myVec3d v, dv, a;

	//belong to k-nearest
	int index_spine, index_joint;
	int bestIndex, lastIndex;
	float minDist, comp, worstBestDist;
	vector<int >index_list;

	//set nodes to a random possition near the spine!
	for (int i = 0; i < numPoints; i++) {

		do {
			//find the spine and find the joint to calc
			index_spine = rand() % (skeleton.size());
			index_joint = rand() % (skeleton[index_spine].joints.size() - 1);

			//calculate the pos of the new node
			// a = s1 - s0;
			a = skeleton[index_spine].joints[index_joint + 1] - skeleton[index_spine].joints[index_joint];
			// v = s0 + a * t; ( 0 < t < 1)
			v = skeleton[index_spine].joints[index_joint] + a * ( static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) );
			// (-threshold < |dv| < threshold)
			dv.setRandomByMag(threshold);
			// v = v + dv;
			v += dv;

		} while (v.inBox(creationSpace) == false);

		//add created node to graph!
		genotype.addNode(v);

		//find nearest nodes and connect them to the new node
		index_list = genotype.getNearestNodesIndex(genotype.back().data, numConnections);

		for (int j = 0; j < index_list.size(); j++) {
			genotype.addEdge(genotype.size() - 1, index_list[j]);
		}
	}
}

void Structure::calcFitness()		////TEMP!!!!!!!!!!!!!!
{
	float len = 0;
	for (int i = 0; i < genotype.numNodes()-1; i++)len += genotype[i].data.dist(genotype[i+1].data);
	fitness = genotype[0].data.dist(genotype[genotype.numNodes()-1].data) / len;
}

void Structure::mutate(float rate_move, float rate_add, float rate_remove)
{
	mutateMove(rate_move, 50);
	//mutateAdd(rate_add);
	//mutateRemove(rate_remove);
}

Structure Structure::crossover(Structure * other)		//TEMP!!!!!!!!!!!!!!
{	
	int new_size = this->getSize();
	if (other->getSize() < new_size)new_size = other->getSize();

	Structure new_s(new_size);
	new_s.setCreationSpace(this->creationSpace);

	for (int i = 0; i < new_size; i++) {
		if(rand() % 2)new_s.genotype.addNode((this->genotype[i].data));
		else new_s.genotype.addNode((other->genotype[i].data));
	}

	return new_s;
}

void Structure::crossover(Structure ** parent, Structure * kid1, Structure * kid2)
{
	int new_size = this->getSize();
	if ((*parent)->getSize() < new_size)new_size = (*parent)->getSize();

	kid1->genotype.clear();
	kid2->genotype.clear();

	kid1->setCreationSpace(this->creationSpace);
	kid2->setCreationSpace(this->creationSpace);


	//This will be the implimentation for the structure development.

	int t_len = this->getSize(), p_len = (*parent)->getSize();
	float dist;
	myVec3d* min, *t_gen, *p_gen, delta;
	vector<int> nabours1, nabours2;

	if (t_len > p_len)t_len = p_len;

	for (int i = 0; i < t_len; i++) {
		t_gen = &(this->genotype[i].data);

		min = &((*parent)->genotype[0].data);
		for (int j = 1; j < p_len; j++) {
			p_gen = &((*parent)->genotype[j].data);

			dist = t_gen->dist((*p_gen));
			if (dist < t_gen->dist(*min))min = p_gen;
		}
		delta = *min - *t_gen;
		kid1->genotype.addNode(*t_gen + delta);
		kid2->genotype.addNode(*min - delta);

		nabours1 = kid1->genotype.getNearestNodesIndex(kid1->genotype.back().data, 3);
		nabours2 = kid2->genotype.getNearestNodesIndex(kid2->genotype.back().data, 3);

		//connect nearest
		for (int j = 0; j < nabours1.size(); j++) {
			kid1->genotype.addEdge(kid1->genotype.size() - 1, nabours1[j]);
			kid2->genotype.addEdge(kid2->genotype.size() - 1, nabours2[j]);
		}

	}



	//This is an example implimentation which calculates the gen with 1/3 and 2/3
	/*
	int t_len = this->getSize(), p_len = (*parent)->getSize();
	float dist;
	myVec3d* min, * t_gen, * p_gen, delta;
	for (int i = 0; i < t_len; i++) {
		t_gen = &(this->genotype[i].data);

		min = &((*parent)->genotype[0].data);
		for (int j = 1; j < p_len; j++) {
			p_gen = &((*parent)->genotype[j].data);

			dist = t_gen->dist((*p_gen));
			if (dist < t_gen->dist(*min))min = p_gen;
		}
		delta = *min - *t_gen;
		kid1->genotype.addNode(*t_gen + delta);
		kid2->genotype.addNode(*min - delta);
	}
	*/

	//This is an example implimentation which selects the gen of parent a or parent b by chance 50%
	/*
	for (int i = 0; i < new_size; i++) {
		switch (rand() % 4) {
			case 0: kid1->genotype.addNode(this->genotype[i]);
					kid2->genotype.addNode(this->genotype[i]);
					break;
			case 1: kid1->genotype.addNode((*parent)->genotype[i]);
					kid2->genotype.addNode(this->genotype[i]);
					break;
			case 2:	kid1->genotype.addNode(this->genotype[i]);
					kid2->genotype.addNode((*parent)->genotype[i]);
					break;
			case 3: kid1->genotype.addNode((*parent)->genotype[i]);
					kid2->genotype.addNode((*parent)->genotype[i]);
		}
	}
	*/

}

vector<float> Structure::getNodeData()
{
	vector<float> data;
	for (int i = 0; i < genotype.numNodes() * 3; i++)data.push_back(genotype[(int)(i / 3)].data.getComp(i % 3));
	return data;
}

string Structure::toString()
{
	stringstream s;
	s << "Struct: size=" << size << ", fitness=" << fitness;
	s <<"\n"<< genotype.toString();
	return s.str();
}


Structure::~Structure()
{
}
