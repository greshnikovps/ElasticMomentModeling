#include "GraphicDrawer.h"
#include "Solver.h"
#include "potentials.h"
#include "Common.h"

int main()
{
	double dt = 0.005;
	double time = 10;
	
	Solver solver;
	Solution solution = solver.solveByEulerMethod(time, dt, U, dU);
	/*
	std::vector<Vector> coordsToPlot(solution.coords.begin() + solution.coords.size() * 95 / 100,
		solution.coords.end());	
	std::vector<Energy> energyToPlot(solution.energy.begin() + solution.energy.size() * 95 / 100,
		solution.energy.end());
	*/
	//GraphicDrawer::drowVectorPlot(solution.coords);
	GraphicDrawer::drowEnergyPlot(solution.energy);

}