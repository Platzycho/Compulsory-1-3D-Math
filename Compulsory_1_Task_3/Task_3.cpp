#include "Task_3.h"
#include <fstream>

double Task_3::f(double x, double y)
{
	return 5 * pow(x ,3) + 2 * y;
}

std::vector<std::vector<double>> Task_3::computeSurface(int resolution)
{
	std::ofstream outFile("output.txt");
	if(!outFile.is_open()) {
		std::cerr << "Unable to open file for writing." << std::endl;
	}
    
	std::vector<std::vector<double>> surface(resolution, std::vector<double>(resolution));
	double x, y;
	double step = 10.0f / (resolution - 1);

	for(int i = 0; i < resolution; ++i){
		x = i * step;
		for(int j = 0; j < resolution; ++j){
			y = j * step;
			surface[i][j] = f(x, y);
			outFile << "Random words: " << f(x, y) << std::endl;
		}
	}
	return surface;
	
}
