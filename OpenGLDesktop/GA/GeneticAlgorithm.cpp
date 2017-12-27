// GeneticAlgorithm.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "PopulationHandler.h"
#include "myGraph.h"
#include "myVec3d.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define popSize 50
#define poolSize 10
#define initStructSize 50
#define connectionsPerNode 5
#define spawnThreshold 100
#define stopGA 100000000
#define timestep 100

#define mutationRate_move 0.05
#define mutationRate_add 0.01
#define mutationRate_remove 0.01

void testGA(int);
void testGraph();
void testStructure();
void testBuild();
void testPath();
void testPath1();
void testMultiSpine();
void testGA_withSkelton(vector<Spine>skeleton, int);
void testVec();
void testHash();

int main()
{
	srand(static_cast <unsigned> (time(0)));		// init random number generation

	testGraph();
	//testStructure();
	//testPath();
	//testPath1();
	//testMultiSpine();
	//testBuild();
	//testGA(stopGA);

	
	//configure skleton
	const int numSpines = 1, numJoints = 2;
	myVec3d skeleton[numSpines][numJoints] = { { myVec3d(0,20,100), myVec3d(1000,10,30) } };
	vector<Spine>blueprint;
	Spine s;
	for (int i = 0; i < numSpines; i++) {
		for (int j = 0; j < numJoints; j++) {
			s.joints.push_back(skeleton[i][j]);
		}
		blueprint.push_back(s);
	}

	testGA_withSkelton(blueprint, stopGA);
	

	//testVec();
	//testHash();

    return 0;
}

void testGA_withSkelton(vector<Spine>skeleton, int stop) {

	cout << "\nSetup Popualtion:\n -popSize: " << popSize << "\n -initStructSize: " << initStructSize << "\n -connections: " << connectionsPerNode << endl;
	cout << "With Skeleton: " << endl;
	PopulationHandler population(popSize, initStructSize);
	population.setCreationSpace(1000, 1000, 1500);
	population.build(skeleton, initStructSize, connectionsPerNode, spawnThreshold);
	//population.random();
	population.calcFitnessValues();
	population.updateStatistics();

	cout << "\nEnd of population setup:\nStop GA in "<< stop << " itreations.\n\nInitValues: ";
	cout << population.toString() << endl;
	cout << "Starting generative process ...\n\n";

	Structure kid1, kid2;
	Structure *parent1, *parent2;

	for (int i = 1; i < stop; i++) {

		population.tournamentSelect(poolSize, &parent1, &parent2);

		//kid1 = parent1->crossover(parent2);
		//kid2 = parent2->crossover(parent1);

		parent1->crossover(&parent2, &kid1, &kid2);

		kid1.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);
		kid2.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);

		kid1.calcFitness();
		kid2.calcFitness();

		population.replace(parent1, parent2, &kid1, &kid2);

		if (i % timestep == 0) {
			population.replaceWorst();
			population.updateStatistics();
			cout << "\rIteration: "<< i << "  " << population.toString() << endl;
			cout << population.showPopulation();
		}
		else if(i % 10 == 0) cout << "\r" << i % timestep << " of " << timestep << " iterations completed.";
	}

	cout << "\n\nEnd of generative process!" << endl << endl;
	population.updateStatistics();
	cout << "Last Statistics: " << population.toString() << endl << endl;
}

void testMultiSpine() {
	// the threshhold from the connections of the spine-joints
	float threshhold = 100;
	//[num Spines][num Joints]
	const int numSpines = 3;
	const int numJoints = 3;
	//config skeleton
	myVec3d skeleton[numSpines][numJoints] = {
		{ myVec3d(0,0,0), myVec3d(1000,0,0), myVec3d(2000,0,0) },
		{ myVec3d(0,0,0), myVec3d(0,1000,0), myVec3d(0,2000,0) },
		{ myVec3d(0,0,0), myVec3d(0,0,1000), myVec3d(0,0,2000) }
	};
	//config num connections and num nodes general
	const int numPoints = 10;
	const int numConnections = 1;

	//--------------------------------------
	myGraph g;
	myVec3d v, dv;

	//belong to k-nearest
	int index_spine, index_joint;
	int bestIndex, lastIndex;
	float minDist, comp, worstBestDist;
	vector<int >index_list;

	//set nodes to a random possition near the spine!
	for (int i = 0; i < numPoints; i++) {

		//find the spine and find the joint to calc
		index_spine = rand() % (numSpines);
		index_joint = rand() % (numJoints - 1);
		//calculate the pos of the new node
		v = skeleton[index_spine][index_joint + 1] - skeleton[index_spine][index_joint];
		v *= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
		v += skeleton[index_spine][index_joint];
		dv.setRandomByMag(threshhold);
		v += dv;

		//add created node to graph!
		g.addNode(v);



		// find k-nearest nabours with broude force methode.
		lastIndex = g.numNodes() - 1; 		//find last index of graph
		worstBestDist = 0; 		//init worstBest with value 0
								//try to connect with nearest nods "numConnections" times
		for (int j = 0; j < numConnections; j++) {

			minDist = LONG_MAX; 		//init minDist with MAX value

										//  go through all nodes (exapt for last because this is the current one)
			for (int k = 0; k < lastIndex; k++) {

				comp = g[k].data.dist(g.back().data);	//set comp to smallest dist to current node

														//set bestIndex to current index k and minDist to comp if new dist is smaller then the best old one and it is biller then the last best one
				if (comp < minDist && comp > worstBestDist) {
					bestIndex = k;
					minDist = comp;
				}
			}

			if (minDist != LONG_MAX) {
				index_list.push_back(bestIndex);	//could be the edges of the node!!! zb. g.back().edges.push_back(g[bestIndex]);
				worstBestDist = minDist;
			}
		}

		// cout << endl << i << ") ";
		// connect nearest naboures to current node
		for (int j = 0; j < index_list.size(); j++) {
			g.addEdge(lastIndex, index_list[j]);
			// cout << index_list[j] << ", ";
		}
		index_list.clear();

	}

	cout << g.toString() << endl;

}

void testPath1() {
	float threshhold = 100;
	const int numPath = 3;
	const int numPoints = 10;
	const int numConnections = 1;
	myVec3d path[numPath] = { myVec3d(0,0,0), myVec3d(1000,0,0), myVec3d(2000,0, 0) };
	myGraph g;
	myVec3d v, dv;

	//belong to k-nearest
	int index, bestIndex, lastIndex;
	float minDist, comp, worstBestDist;
	vector<int >index_list;
	
	//set nodes to a random possition near the spine!
	for (int i = 0; i < numPoints; i++) {
		index = rand() % (numPath-1);
		v = path[index + 1] - path[index];
		v *= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX ));
		v += path[index];
		dv.setRandomByMag(threshhold);
		v += dv;
		g.addNode(v);



		// find k-nearest nabours with broude force methode.
		lastIndex = g.numNodes() - 1; 		//find last index of graph
		worstBestDist = 0; 		//init worstBest with value 0
			//try to connect with nearest nods "numConnections" times
		for (int j = 0; j < numConnections; j++) {

			minDist = LONG_MAX; 		//init minDist with MAX value

			//  go through all nodes (exapt for last because this is the current one)
			for (int k = 0; k < lastIndex; k++) {
				
				comp = g[k].data.dist(g.back().data);	//set comp to smallest dist to current node

				//set bestIndex to current index k and minDist to comp if new dist is smaller then the best old one and it is biller then the last best one
				if (comp < minDist && comp > worstBestDist) {
					bestIndex = k;
					minDist = comp;
				}
			}

			if (minDist != LONG_MAX) {
				index_list.push_back(bestIndex);	//could be the edges of the node!!! zb. g.back().edges.push_back(g[bestIndex]);
				worstBestDist = minDist;
			}
		}

		// cout << endl << i << ") ";
		// connect nearest naboures to current node
		for (int j = 0; j < index_list.size(); j++) { 
			g.addEdge(lastIndex, index_list[j]); 
			// cout << index_list[j] << ", ";
		}
		index_list.clear();
		
	}

	cout << g.toString() << endl;
	
}

void testPath() {
	myGraph graph;
	const int numPath = 3;
	const int numPoints = 4;
	const int numConnections = 1;
	myVec3d path[numPath] = { myVec3d(0,0,0), myVec3d(1000,1000,1000) };
	myVec3d v;
	int bestIndex = 0, num;
	while(graph.numNodes() < numPoints){
		v.setRandom(1000);

		for (int j = 0; j < numPath - 1; j++) {

			if (v.nearLine(path[j], path[j + 1], 100)) {									//chack if the new Point is near the Line (Path)
				graph.addNode(v);															// if so add it to the Graph
				num = graph.numNodes() - 1;
				for (int k = 0; k < numConnections; k++) {
					for (int l = 0; l < num; l++) {
						if (graph[l].data.dist(graph.back().data) < graph[bestIndex].data.dist(graph.back().data) &&
							graph.isConnected(num, l) == false ) {
							bestIndex = l;
						}
					}
					cout << num << " & " << bestIndex << endl;
					graph.addEdge(num, bestIndex);
					bestIndex = 0;
				}
				break;																		//break if the Point is near one Path so not all Paths have to be visited.
			}
		}
	}
	cout << graph.toString() <<endl;
}

void testBuild() {
	const int d = 24;
	const int numLeaf = 5;
	myVec3d s(0, 0, 0), g(0, 0, 15);	//start and goal
	myVec3d r[d];	//root
	myVec3d l[d][numLeaf];	//leaf
	cout << "s: " << s.toString() << " g: " << g.toString() << endl;
	for (int i = 0; i < d; i++) {
		r[i].set(s + (g - s) * (i + 1) / (d + 1));
		cout << r[i].toString() << ", ";
	}
	cout << endl;
	myVec3d vec;
	for (int i = 0; i < d; i++) {
		vec.setRandom(-5, 5);
		r[i] += vec;
		cout << r[i].toString() << ", ";
	}
	cout << endl << "leaf matrix:" << endl;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < numLeaf; j++) {
			vec.setRandom(-2.5, 2.5);
			l[i][j].set(r[i] + vec);
			cout << l[i][j].toString() << ", ";
		}
		cout << endl;
	}

	cout << endl;
}

void testGA(int stop) {

	cout << "\nSetup Popualtion:\n -popSize: " << popSize << "\n -initStructSize: " << initStructSize << endl;
	PopulationHandler population(popSize, initStructSize);
	population.setCreationSpace(800, 1000, 10);
	population.random();
	population.calcFitnessValues();
	population.updateStatistics();

	cout << "\nEnd of population setup:\nInitValues: ";
	cout << population.toString() << endl;
	cout << "Starting generative process ...\n\n";

	Structure kid1, kid2;
	Structure *parent1, *parent2;

	for (int i = 1; i < stop; i++) {

		population.tournamentSelect(poolSize, &parent1, &parent2);

		//kid1 = parent1->crossover(parent2);
		//kid2 = parent2->crossover(parent1);

		parent1->crossover(&parent2, &kid1, &kid2);

		kid1.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);
		kid2.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);

		kid1.calcFitness();
		kid2.calcFitness();

		population.replace(parent1, parent2, &kid1, &kid2);

		if (i % 1000 == 0) {
			population.replaceWorst();
			population.updateStatistics();
			cout << population.toString() << endl;
		}
	}

	cout << "\n\nEnd of generative process!" << endl << endl;
	population.updateStatistics();
	cout << "Last Statistics: " << population.toString() << endl << endl;
}

void testStructure() {

	Structure s(10);
	
	s.randomStructure(100, 100, 500);
	s.mutate(mutationRate_move, mutationRate_add, mutationRate_remove);
	cout << s.toString() << endl;

}

void testHash() {

	myVec3d space(1000, 1000, 1000);

	myVec3d v(0, 0, 500);
	myVec3d v1(0, 0, 501);

	cout << v.hash(space) << " = " << v.hash(space).to_ulong() <<endl;
	cout << v1.hash(space) << " = " << v1.hash(space).to_ulong() << endl;

}
void testVec() {

	myVec3d space(1000, 1000, 1000);
	vector<myVec3d> vec;

	myVec3d v;

	v.setRandom(space);
	vec.push_back(v);
	int l = 0, r = vec.size(), m;
	unsigned long hash;
	for (int i = 0; i < 5; i++) {

		v.setRandom(space);
		hash = v.hash(space).to_ulong();
		while (l < r) {
			m = (int)((l + r) / 2);			
			if (vec[m].hash(space).to_ulong() < hash)l = m;
			else r = m;
		}
		vec.insert(vec.begin() + m, v);
		cout << vec.back().toString() << ", ";
	}
	cout << endl;
}

void testGraph() {
	myGraph g;
	myVec3d vec;
	for (int i = 0; i < 10; i++) {
		vec.setRandom(5, 22.57);
		g.addNode(vec);
	}

	g.at(9).data.x = 10;
	g[9].data.y = 20;
	g.addEdge(5, 6);
	cout << g.toString() << endl;
	cout << "is 5 connected to 6: " << g.isConnected(5, 6) << endl;
	g.deleteNode(5);
	cout << g.toString() << endl;
	cout << "is 5 connected to 6: " << g.isConnected(5, 6) << endl;

	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	cout << g.toString() << endl;
	vector<myVec3d *> arr = g.getConnectedData(1);
	cout << "connection 1, 4 ?: " << g.isConnected(1, 4);
	g.deleteEdge(1, 4);
	cout << "connection 1, 4 ?: " << g.isConnected(1, 4);
	for (int i = 0; i < arr.size(); i++)cout << arr[i]->toString();
	cout << " Size: " << arr.size() << endl;
	arr[1]->z = 30;
	cout << g.toString() << endl;

}

