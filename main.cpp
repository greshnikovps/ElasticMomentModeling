#include "GraphicDrawer.h"
#include "Solver.h"
#include "potentials.h"
#include "Common.h"
#include "equasion.h"

int main()
{
	double dt = 0.0001;
	double time = 25;
	
	Solver solver;
	Solution solution = solver.solveByRungeKuttaMethod(time, dt, U, dU, dotOmega, dotPhi);
	//Solution solution = solver.solveByEulerMethod(time, dt, U, dU);
	
	/*
	std::vector<Vector> coordsToPlot(solution.coords.begin() + solution.coords.size() * 95 / 100,
		solution.coords.end());	
	std::vector<Energy> energyToPlot(solution.energy.begin() + solution.energy.size() * 95 / 100,
		solution.energy.end());
	*/


	GraphicDrawer::drowVectorPlot(solution.coords, dt);
	GraphicDrawer::drowEnergyPlot(solution.energy, dt);

}