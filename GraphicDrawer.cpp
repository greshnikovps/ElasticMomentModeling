#include "GraphicDrawer.h"
#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"

void GraphicDrawer::drowVectorPlot(const std::vector<Vector>& data)
{
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	std::vector<double> magn(data.size());
	std::vector<double> time(data.size());

	for (size_t i = 0; i < data.size(); i++) {
		magn[i] = data[i].magnitude();
		time[i] = i;
	}

	StringReference errorMessage;
	DrawScatterPlot(imageReference, 600, 400, &time, &magn, &errorMessage);

	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "coords.png");

	std::cout << "drowVectorPlot " << data.size() << std::endl;
}

void GraphicDrawer::drowScalarPlot(const std::vector<double>& data)
{
	std::cout << "drowScalarPlot" << data.size() << std::endl;
}

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

void GraphicDrawer::drowEnergyPlot(const std::vector<Energy>& data)
{
	std::vector<double> kinetic(data.size());
	std::vector<double> potential(data.size());
	std::vector<double> total(data.size());
	std::vector<double> time(data.size());

	for (size_t i = 0; i < data.size(); i++) {
		kinetic[i] = data[i].kinetic;
		potential[i] = data[i].potential;
		total[i] = data[i].total;
		time[i] = i;
	}

	StringReference* errorMessage = new StringReference();
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries* totalSeries = setSeries(time, total, CreateRGBColor(1, 0, 0));

	ScatterPlotSeries* kineticSeries = setSeries(time, kinetic, CreateRGBColor(0, 1, 0));

	ScatterPlotSeries* potentialSeries = setSeries(time, potential, CreateRGBColor(0, 0, 1));

	ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
	settings->width = 2400;
	settings->height = 1600;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"x^2 - 2");
	settings->xLabel = toVector(L"X axis");
	settings->yLabel = toVector(L"Y axis");

	settings->scatterPlotSeries->push_back(totalSeries);
	settings->scatterPlotSeries->push_back(kineticSeries);
	settings->scatterPlotSeries->push_back(potentialSeries);

	DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "energy.png");	
}
