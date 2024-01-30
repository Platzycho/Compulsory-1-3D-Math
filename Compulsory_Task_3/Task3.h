#pragma once
#include <iostream>
#include <vector>
class Task_3
{
public:
	double f(double x, double y);

	std::vector<std::vector<double>> computeSurface(int resolution);

	std::vector<float> createVertices(const std::vector<std::vector<double>>& surface);
};

