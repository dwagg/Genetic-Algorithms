#include <algorithm>
#include <iterator>
#include <functional>
#include <time.h>
#include <iostream>
#include <fstream>
#include "IterationManager.h"
#include "Iteration.h"
#include "Story.h"

IterationManager::IterationManager()
{
	iterations.push_back(Iteration());
}
IterationManager::IterationManager(int velosity)
{
	this->velosity = velosity;
	buildBacklog();
	Story stories[15][24];
	for (int j = 0; j < 10; ++j)
	{
		for (int i = 0;i < (int)(velosity * .8); ++i)
		{
			stories[j][i] = backlog.at((velosity * .8 * j) + i);
		}
//		backlog.erase(backlog.begin(), backlog.begin() + (int)(velosity * .8));
		iterations.push_back(Iteration(velosity, stories[j]));
	}

}

bool sortingIterations(Iteration& lhs, Iteration& rhs)
{
	return lhs.getFitness() < rhs.getFitness();
}

void IterationManager::sortIterations()
{
	std::sort(iterations.begin(), iterations.end());
}

//calling cullIterations will automatically draw down the number of iterations by over 80%
//This is culling too many. reduce the number culled.
void IterationManager::cullIterations()
{
	iterations.resize(20);
//	iterations.erase(iterations.begin());
}


//This will by a pairwise selection of stories sorted within each Iteration.
//Starting with 20 parents and doing combinatorial pairing will result in 20 choose 2 iterations per generation 
void IterationManager::mergeIterations()
{
	for (unsigned int i = 0; i < 20 - 1; ++i)
	{
		for (unsigned int j = i + 1; j < 20; ++j)
		{
			iterations.push_back(Iteration::merge(iterations[i], iterations[j], velosity));
			iterations.push_back(Iteration::merge(iterations[j], iterations[i], velosity));

		}
	}
}

//I will be getting a random number, ensure that this ID is not in the current iteration I am looking at and switching some random story from this iteration with 
//the story from the storyPool that  has that ID//
void IterationManager::mutate() 
{
	bool mutated = false;
	int iterToMutate = rand() % this->iterations.size();
	while (!mutated) 
	{
		int id = rand() % backlog.size();
		int storyToMutate = rand() % iterations[iterToMutate].getNumOfStories();
		if (! iterations[iterToMutate].containsStory(id))
		{
			iterations[iterToMutate].replaceStory(backlog.at(storyToMutate),storyToMutate);
			mutated = true;
		}
		
	}
}

void IterationManager::runSimulation()
{
	std::ofstream outputFile;
	outputFile.open("GAoutput.csv");
	int generations = 200;
	for (int i = 0; i <= generations; ++i)
	{
		mergeIterations();
		sortIterations();
		cullIterations();
		if (i % 8 == 0)
		{
			mutate();
			mutate();
			mutate();
			mutate();
			mutate();
			mutate();
		}
		if (i % 2 == 0) 
		{
			std::cout << "Max fitness in generation " << i << ": " << iterations[0].getFitness() << std::endl;
			outputFile << i << ',' << iterations[0].getFitness() << std::endl;
		}

	}
	std::cout << "Stories in the best iteration:";
	iterations[0].printStories();
	
	outputFile.close();
}

void IterationManager::buildBacklog()
{
	int numOfStories = 1000;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < numOfStories; ++i)
	{
		int dependence[10];
		int dependentNdx = 0;
		int points;
		int pointGroup = rand() % 20;
		
		for (int i = dependentNdx; i < 10; ++i) {
			dependence[i] = -1;
		}
		//45 percent the population for 3 point stories//
		if (pointGroup < 9)
		{
			points = 3;
		}
		//20 percent the population for 2 point stories
		else if (pointGroup < 13)
		{
			points = 2;
		}
		// 10 % for 1 point 
		else if (pointGroup < 15)
		{
			points = 1;
		}
		//15 % for 5 point 
		else if (pointGroup < 18)
		{
			points = 5;
		}
		//5 % for 8 points
		else if (pointGroup < 19)
		{
			points = 8;
		}
		//5 % for 13 points
		else
		{
			points = 13;
		}
		backlog.push_back(Story(i, rand() % 50 + 1, points, dependence));
	}
}