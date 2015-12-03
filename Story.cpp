#include "Story.h"

Story::Story()
{
	id = 0;
	priority = 0;
//	pointsEarned = 0;
	pointsLeft = 0;
	//for (int i = 0; i < 10; ++i)
	//{
	//	this->dependence.push_back(-1);
	//}
}
//
//I think that this constructor is necessary because of the dependency issue though maybe it could be handled differently.
Story::Story(int id, int priority, int pointsLeft, int dependence[])
{
	this->id = id;
	this->priority = priority;
//	pointsEarned = 0;
	priorityDensity = priority / (float)pointsLeft;
	this->pointsLeft = pointsLeft;

	//for (int i = 0; i < 10; ++i) 
	//{
	//	this->dependence.push_back(dependence[i]);
	//}

}

int Story::getPriority()
{
	return priority;
}
//these two points attributes may become one single attribute
//int Story::getPointsEarned() 
//{
//	return pointsEarned;
//}

int Story::getPointsLeft() 
{
	return pointsLeft;
}

//unique to each story
int Story::getId()
{
	return id;
}

//priority density is the priority of a story over the points the story is worth. this is an attempt to even out the priority better than a pure average
float Story::getPriorityDensity() 
{
	return priorityDensity;
}

//std::vector<int> Story::getDependents()
//{
//	return dependence;
//}

//priority is an attribute of each story that is provided to this application and can be assumed to exist and be 1-50. a 0 priority means not sized yet
void Story::setPriority(int priority) 
{
	this->priority = priority;
}

//consolidating points left and points earned as it has no impact on simulation.
//though possible every once in a while adding a new story that is some leftovers might make sense. 
//void Story::setPointsEarned(int pointsEarned) 
//{
//	this->pointsEarned = pointsEarned;
//}

void Story::setPointsLeft(int pointsLeft) 
{
	this->pointsLeft = pointsLeft;
}
//Wary of this and the Iteration version of this function. revisit to fix errors

