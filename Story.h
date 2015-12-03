#ifndef _STORY_
#define _STORY_
#include <vector>
class Story {
private:
	int id;
//	std::vector<int> dependence;
	int priority;
//	int pointsEarned;
	int pointsLeft;
	float priorityDensity;
	//
public:
	Story();
	Story(int id, int priority, int pointsLeft, int dependence[]);
	int getPriority();
//	int getPointsEarned();
	int getPointsLeft();
	int getId();
	float getPriorityDensity();
//	std::vector<int> getDependents();
	void setPriority(int priority);
//	void setPointsEarned(int pointsEarned);
	void setPointsLeft(int pointsLeft);
	bool operator<(const Story& rhs) const { return priorityDensity > rhs.priorityDensity; }
};

#endif 