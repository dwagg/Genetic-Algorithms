#ifndef _ITERATION_
#define _ITERATION_

#include <vector>
#include "Story.h"

const int MAX_STORIES = 30;

class Iteration {
private:
	
	std::vector<Story> stories;
	float fitness;
	int velosity;
	int points;
	int delta; //points - velosity
	//
public:
	Iteration();
	Iteration(int velosity, Story stories[]);
	Iteration(int velosity, std::vector<Story> stories);
	~Iteration();
	int getNumOfStories();
	float getFitness();
	int getVelosity();
	int getPoints();
	int getDelta();
	void calculateFitness();
	void calculateDelta();
	void setVelosity(int velosity);
	void setPoints(int points);
	void setFitness(float fitness);
	void setStories(Story stories[], int to);
	void printStories();
	bool operator<(const Iteration& rhs) const { return fitness > rhs.fitness; }

	//Story at(int ndx);
	bool containsStory(int id);
	void replaceStory(Story toReplaceWith,int id);
	static Iteration merge(Iteration lhs, Iteration rhs, int velosity);
};

#endif
