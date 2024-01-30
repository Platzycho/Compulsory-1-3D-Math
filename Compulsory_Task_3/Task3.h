#pragma once
#include <iostream>
#include <vector>
class Task_3
{
public:
	struct vertex
	{
		float x, y, z;
		float r, g, b;
	};

	std::vector<vertex*> vertices;

	double f(double x, double y);

	void generateVertices();

	vertex* createVertex(const float x, const float y, const float z, const float r, const float g, const float b);

	std::vector<std::vector<double>> computeSurface(double resolution);

	std::vector<float> createVertices(const std::vector<std::vector<double>>& surface);
};

