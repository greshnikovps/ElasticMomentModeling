#include "GraphicDrawer.h"
#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"

ScatterPlotSeries* setSeries(std::vector<double>& x, std::vector<double>& y, RGBA* color) {
	ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &x;
	series->ys = &y;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");
	series->lineThickness = 2;
	series->color = color;
	return series;
}

void GraphicDrawer::drowVectorPlot(const std::vector<Vector>& data, const double& dt)
{
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	std::vector<double> magn(data.size());
	std::vector<double> time(data.size());

	for (size_t i = 0; i < data.size(); i++) {
		magn[i] = data[i].magnitude();
		time[i] = i * dt;
	}

	StringReference errorMessage;

	ScatterPlotSeries* coordSeries = setSeries(time, magn, CreateRGBColor(1, 0, 0));

	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"");
	settings->xLabel = toVector(L"t");
	settings->yLabel = toVector(L"");

	settings->scatterPlotSeries->push_back(coordSeries);

	DrawScatterPlotFromSettings(imageReference, settings, &errorMessage);

	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "coords.png");

	std::cout << "drowVectorPlot " << data.size() << std::endl;
}

void GraphicDrawer::drowScalarPlot(const std::vector<double>& data)
{
	std::cout << "drowScalarPlot" << data.size() << std::endl;
}



void GraphicDrawer::drowEnergyPlot(const std::vector<Energy>& data, const double& dt)
{
	std::vector<double> kinetic(data.size());
	std::vector<double> potential(data.size());
	std::vector<double> total(data.size());
	std::vector<double> time(data.size());

	for (size_t i = 0; i < data.size(); i++) {
		kinetic[i] = data[i].kinetic;
		potential[i] = data[i].potential;
		total[i] = data[i].total;
		time[i] = i * dt;
	}

	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries* totalSeries = setSeries(time, total, CreateRGBColor(1, 0, 0));

	ScatterPlotSeries* kineticSeries = setSeries(time, kinetic, CreateRGBColor(0, 1, 0));

	ScatterPlotSeries* potentialSeries = setSeries(time, potential, CreateRGBColor(0, 0, 1));

	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 800;
	settings->height = 600;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"Energy of the system");
	settings->xLabel = toVector(L"t");
	settings->yLabel = toVector(L"Energy");

	settings->scatterPlotSeries->push_back(totalSeries);
	settings->scatterPlotSeries->push_back(kineticSeries);
	settings->scatterPlotSeries->push_back(potentialSeries);

	DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "energy.png");	
}
