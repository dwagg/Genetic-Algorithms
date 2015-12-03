#include <iostream>
#include <random>
#include <time.h>
#include "IterationManager.h"
#include "Iteration.h"
#include "Story.h"

//prototypes
void storyBuilder(Story stories[], const int numOfStories);

int main(int argc, char** argv, char** envp)
{
	const int numOfStories = 100;
//	Story stories[numOfStories];
//	storyBuilder(stories, numOfStories);
//	std::vector<Story> backlog(stories, stories + sizeof stories / sizeof stories[0]);
	IterationManager manager = IterationManager( 30);
	manager.runSimulation();
	//Story stories2[30];
	//for (int i = 0; i < 30; ++i)
	//{
	//	stories2[i] = Story(stories[42 + i]);
	//}
	//Iteration iteration = Iteration(30, stories);
	//Iteration iteration2 = Iteration(30, stories2);
	//Iteration child = Iteration::merge(iteration, iteration2,30);
	std::cin.get();
	return 0;
}

//builds stories, with more time it would be customizable and extensable
void storyBuilder(std::vector<Story> stories, const int numOfStories)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < numOfStories; ++i)
	{
		int dependence[10];
		int dependentNdx = 0;
		int points;
		int pointGroup = rand() % 20;
		if (i % 14 == 0) {
			dependence[dependentNdx] = rand() % 100;
			++dependentNdx;
		}

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
		stories[i] = Story(i, rand() % 50, points, dependence);
	}

}