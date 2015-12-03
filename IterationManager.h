#ifndef _ITERATION_MANAGER_
#define _ITERATION_MANAGER_
#include <vector>
#include "Iteration.h"
#include "Story.h"
class IterationManager {
private:
	int velosity;
	std::vector<Iteration> iterations;
	std::vector<Story> backlog;
	void sortIterations();
	void cullIterations();
	void mergeIterations();
	void mutate();
	void buildBacklog();
public:
	IterationManager();
	IterationManager(int velosity);
	void runSimulation();
	static bool sortingIterations(Iteration lhs, Iteration rhs);
};

#endif
