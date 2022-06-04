#pragma once
#include "Common.h"

class GraphicDrawer
{
public:

	/**
	 * Drows data plot.
	 * 
	 * \param data 
	 */
	static void drowVectorPlot(const std::vector<Vector>& data, const double& dt);

	/**
	 * Drows data plot.
	 * 
	 * \param data
	 */
	static void drowScalarPlot(const std::vector<double>& data);

	/**
	 * Drows data plot.
	 * 
	 * \param data
	 */
	static void drowEnergyPlot(const std::vector<Energy>& data, const double& dt);
};

