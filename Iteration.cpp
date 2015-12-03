#include <algorithm>
#include <functional>
#include <iostream>
#include "Iteration.h"
#include "Story.h"

//all the getters and setters are available to make this constructor work just fine
Iteration::Iteration() 
{

	//consider taking velosity out of Iteration as it is a team attribute and not an iteration attribute.>|< >|< >|< >|< >|< >|<//
	velosity = 0;
	points = 0;
	for (int i = 0; i < MAX_STORIES; ++i) {
		Story* newStory = new Story();
		stories.push_back(*newStory);
	}
	delta = 0;
	fitness = -1;
}

Iteration::~Iteration() 
{

}

//Look into if this constructor is necessary
Iteration::Iteration(int velosity, Story stories[])
{
	this->velosity = velosity;
	this->points = 0;
	
	for (int i = 0; i < MAX_STORIES; ++i) 
	{
		points += stories[i].getPointsLeft();
		if (points < velosity + (velosity * 0.1) && stories[i].getPointsLeft() > 0)
		{
			Story* newStory = new Story(stories[i]);
			this->stories.push_back(*newStory);
		}
		else
		{
			points -= stories[i].getPointsLeft();
			i = MAX_STORIES;
		}
	}
	this->delta = points - velosity;
	calculateFitness();
}

Iteration::Iteration(int velosity, std::vector<Story> stories)
{
	this->velosity = velosity;
	this->points = 0;

	for (int i = 0; i < stories.size(); ++i)
	{
		int pointsLeft = stories[i].getPointsLeft();
		points += pointsLeft;
		this->stories.push_back(Story(stories[i]));
		//if (points < velosity + (velosity * 0.1) && pointsLeft > 0)
		//{
		//	Story* newStory = new Story(stories[i]);
		//	this->stories.push_back(*newStory);
		//}
		//else
		//{
		//	points -= stories[i].getPointsLeft();
		//	i = MAX_STORIES;
		//}
	}
	this->delta = points - velosity;
	calculateFitness();

}
//this is a key hueristic and probably should be looked into more closely
void Iteration::calculateFitness() {
	float priority = 0;
	for (auto i : stories) 
	{
	//	auto dependents = i.getDependents();
		priority += i.getPriorityDensity();
	}
	fitness =(float) (priority * this->points) - abs(delta * velosity);
}

float Iteration::getFitness()
{
	return fitness;
}

int Iteration::getVelosity()
{
	return velosity;
}

int Iteration::getPoints()
{
	return points;
}

//delta = points - velosity
int Iteration::getDelta()
{
	return delta;
}

int Iteration::getNumOfStories()
{
	return stories.size();
}

void Iteration::setVelosity(int velosity)
{
	this->velosity = velosity;
}
void Iteration::setPoints(int points)
{
	this->points = points;
}

void Iteration::setFitness(float fitness)
{
	this->fitness = fitness;
}

void Iteration::setStories(Story stories[], int to)
{
	for (int i = 0; i < to; ++i)
	{
		this->stories.push_back(stories[i]);
	}
}

void Iteration::replaceStory(Story toReplaceWith, int id)
{
	stories[id] = toReplaceWith;
	calculateFitness();
}


//I need the ability to see how far from the velosity we were
void Iteration::calculateDelta()
{
	delta = points - velosity;
}

bool Iteration::containsStory(int id)
{
	for (auto i : stories)
	{
		if (id == i.getId())
			return true;
	}
	return false;
}

Iteration Iteration::merge(Iteration lhs, Iteration rhs, int velosity) 
{
	int points = 0;
	std::vector<Story> stories;
	bool uniqueStory = true;
	for (int i = 0; points <= velosity + (velosity * 0.1) && i < 30; ++i)
	{
		uniqueStory = true;
		bool isOdd = i % 2 ==0;
		if (isOdd && lhs.stories.size() > i/2) 
		{
			for (int j = 0; j < stories.size(); ++j) {
				if (stories.at(j).getId() == lhs.stories.at(i / 2).getId())
					uniqueStory = false;
			}
			if (uniqueStory) {
				stories.push_back(lhs.stories.at(i / 2));
				points += lhs.stories.at(i / 2).getPointsLeft();
			}
		}
		else if (!isOdd && rhs.stories.size() > i / 2)
		{
			for (int j = 0; j < stories.size(); ++j) {
				if (stories.at(j).getId() == rhs.stories.at(i / 2).getId())
					uniqueStory = false;
			}
			if (uniqueStory) {
				stories.push_back(rhs.stories.at(i / 2));
				points += rhs.stories.at(i / 2).getPointsLeft();
			}
		}
	}
	if (points > velosity + (velosity * 0.1)) 
	{
		stories.pop_back();
	}

	return  Iteration(velosity, stories);
}

void Iteration::printStories() {
	for (int i = 0; i < stories.size(); i++) {
		std::cout << stories[i].getId() << ' ';
	}
}