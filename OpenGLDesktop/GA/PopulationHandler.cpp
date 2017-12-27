#include "PopulationHandler.h"

struct {
	bool operator()(Structure a, Structure b) const
	{
		return a.getFitness() < b.getFitness();
	}
} customLess;

void PopulationHandler::updateStatistics()
{	
	auto result = std::minmax_element(population.begin(), population.end(), customLess);
	stats.worstFitness = result.first->getFitness();
	stats.bestFitness = result.second->getFitness();

	float avr = std::accumulate(population.begin(), population.end(), population.begin()->getFitness(), [](float a, Structure b) {return a + b.getFitness(); });
	stats.avrFitness = avr / population.size();
	
	stats.generationCount++;
}

PopulationHandler::PopulationHandler()
{
	srand(static_cast <unsigned> (time(0)));		// init random number generation

	popSize = 0;
	initStructSize = 0;
}

PopulationHandler::PopulationHandler(int populationSize)
{
	srand(static_cast <unsigned> (time(0)));		// init random number generation

	popSize = populationSize;
	initStructSize = 0;
	for (int i = 0; i < popSize; i++)population.push_back(Structure());
}

PopulationHandler::PopulationHandler(int populationSize, int strucSize)
{
	srand(static_cast <unsigned> (time(0)));		// init random number generation

	popSize = populationSize;
	initStructSize = strucSize;

	for (int i = 0; i < popSize; i++)population.push_back(Structure(initStructSize));
}

int PopulationHandler::getPopulationSize()
{
	return population.size();
}

Structure & PopulationHandler::operator[](int i)
{
	return population[i];
}

void PopulationHandler::setCreationSpace(float w, float d, float h)
{
	for (int i = 0; i < population.size(); i++)population[i].setCreationSpace(myVec3d(w, d, h));
}

void PopulationHandler::random()
{
	for (int i = 0; i < population.size(); i++)population[i].randomStructure();
}

void PopulationHandler::build(vector<Spine> skeleton, int numPoints, int numConnections, int threshold)
{
	cout << endl;
	for (int i = 0; i < population.size(); i++) {
		population[i].buildStructure(skeleton, numPoints, numConnections, threshold);
		cout << "\r" << i+1 << " of " << population.size() << " finished building.";
	}
	cout << endl;
}

void PopulationHandler::calcFitnessValues()
{	
	for (int i = 0; i < population.size(); i++)population[i].calcFitness();
	cout << "Fitness values for population calculated." << endl;
}

Structure * PopulationHandler::tournamentSelect(int selectionPoolSize)
{
	int r, size = population.size();
	
	Structure* best = &population[(rand() % size)];

	for (int i = 0; i < selectionPoolSize; i++) {
		r = rand() % size;

		if (best->getFitness() < population[r].getFitness()) { best = &population[r]; }
	}
	return best;
}

void PopulationHandler::tournamentSelect(int selectionPoolSize, Structure ** p1, Structure ** p2)
{
	int r, size = population.size();

	(*p1) = &population[0];
	(*p2) = &population[0];
	for (int i = 0; i < selectionPoolSize; i++) {
		r = rand() % size;

		if ((*p1)->getFitness() < population[r].getFitness()) {
			(*p2) = (*p1);
			(*p1) = &population[r];
		}
		else if ((*p2)->getFitness() < population[r].getFitness() && population[r].getFitness() < (*p1)->getFitness()) {
			(*p2) = &population[r];
		}
	}
}

void PopulationHandler::replace(Structure * p1, Structure * p2, Structure * k1, Structure * k2)
{
	const int len = 4;
	Structure* arr[len] = { p1, p2, k1, k2 };
	
	int largestA = 0, largestB = 0;

	for (int i = 0; i < len; i++) {
		if (arr[i]->getFitness() > arr[largestA]->getFitness()) {
			largestB = largestA;
			largestA = i;
		}
		else if (arr[i]->getFitness() > arr[largestB]->getFitness() && arr[i]->getFitness() < arr[largestA]->getFitness()) {
			largestB = i;
		}
	}

	if (p1 != arr[largestA])*p1 = *arr[largestA];
	if (p2 != arr[largestB])*p2 = *arr[largestB];

}

void PopulationHandler::replaceWorst()
{
	struct {
		bool operator()(Structure a, Structure b) const
		{
			return a.getFitness() < b.getFitness();
		}
	} customLess;
	//*(std::min_element(std::begin(population), std::end(population), customLess)) = population[rand() % population.size() ];

	auto result = std::minmax_element(std::begin(population), std::end(population), customLess);
	*(result.first) = *(result.second);
}

void PopulationHandler::setInitStructureSize(int structSize)
{
	initStructSize = structSize;
	for (int i = 0; i < population.size(); i++)population[i].setSize(initStructSize);
}

int PopulationHandler::getInitStructureSize()
{
	return initStructSize;
}

vector<float> PopulationHandler::getBestStructureData()
{
	auto result = std::max_element(std::begin(population), std::end(population), customLess);
	return result->getNodeData();
}

string PopulationHandler::toString()
{
	stringstream s;
	s <<"popSize: " << popSize << ", maxFit: " << stats.bestFitness * 100 << ", avrFit: " << stats.avrFitness * 100 << ", minFit: " << stats.worstFitness * 100;
	return s.str();
}

string PopulationHandler::showPopulation()
{
	vector<float> data = getBestStructureData();
	stringstream s;
	//for (int i = 0; i < population.size(); i++)s << i << ": " << &population[i] << ", " << population[i].toString() << endl;
	for (int i = 0; i < data.size(); i++)s << data[i] << ", ";
	return s.str();
}

PopulationHandler::~PopulationHandler()
{
}
