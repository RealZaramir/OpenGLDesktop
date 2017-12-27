#pragma once

#include "Structure.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class PopulationHandler
{

private:	

	struct statistics
	{
		float bestFitness = 0;
		float worstFitness = 0;
		float avrFitness = 0;

		int generationCount = -1;
		
	};	//structure for statistic values 

	statistics stats;

	vector<Structure> population;	//population array

	int popSize;
	int initStructSize;


public:
	PopulationHandler();
	PopulationHandler(int populationSize);
	PopulationHandler(int populationSize, int strucSize);
	
	int getPopulationSize();
	Structure& operator[](int i);
	void setCreationSpace(float w, float d, float h);
	void random();
	void build(vector<Spine> skeleton, int numPoints, int numConnections, int threshold);
	void calcFitnessValues();

	Structure* tournamentSelect(int selectionPoolSize);
	void tournamentSelect(int selectionPoolSize, Structure ** p1, Structure ** p2);

	void replace(Structure* p1, Structure* p2, Structure * k1, Structure * k2);
	void replaceWorst();
	void setInitStructureSize(int structSize);
	int getInitStructureSize();

	vector<float> getBestStructureData();

	string toString();
	string showPopulation();
	void updateStatistics();


	~PopulationHandler();
};

