#include "Task3.h"
#include <fstream>
#include <string>

double Task_3::f(double x, double y)
{
	return 5 * pow(x ,3) + 2 * y;
}

//void Task_3::generateVertices()
//{
//	float resolution = 0.5;
//	for(float x = 0; x < 10; x+=resolution)
//	{
//		for(float y = 0; y < 10; y+=resolution)
//		{
//			float z = f(x, y);
//			vertices.push_back(createVertex(x, y, z, x/10, y/10, z/10));
//
//			float z = f(x + resolution, y);
//			vertices.push_back(createVertex(x + resolution, y, z, x/10 + resolution, y/10, z/10));
//
//			float z = f(x, y + resolution);
//			vertices.push_back(createVertex(x, y + resolution, z, x/10, y/10 + resolution, z/10));
//
//			float z = f(x + resolution, y);
//			vertices.push_back(createVertex(x + resolution, y, z, x/10 + resolution, y/10, z/10));
//
//			float z = f(x, y + resolution);
//			vertices.push_back(createVertex(x, y + resolution, z, x/10, y/10 + resolution, z/10));
//
//			float z = f(x + resolution, y + resolution);
//			vertices.push_back(createVertex(x + resolution, y + resolution, z, x/10 + resolution, y/10 + resolution, z/10));
//		}
//	}
//}
//
//Task_3::vertex* Task_3::createVertex(const float _x, const float _y, const float _z, const float _r, const float _g, const float _b)
//{
//	Task_3::vertex* newVert = new vertex();
//	newVert->x = _x;
//	newVert->y = _y;
//	newVert->z = _z;
//	newVert->r = _r;
//	newVert->g = _g;
//	newVert->b = _b;
//	return newVert;
//}

std::vector<std::vector<double>> Task_3::computeSurface(double resolution)
{
	std::ofstream outFile("output.tmp");
	if(!outFile.is_open()) {
		std::cerr << "Unable to open file for writing." << std::endl;
	}
    
	std::vector<std::vector<double>> surface(resolution, std::vector<double>(resolution));
	double x, y;
	double step = 10.0f / (resolution);
	int lineCount = 0;

	for(int i = 0; i < 10; i+=resolution){
		x = i * step;
		for(int j = 0; j < 10; j+=resolution){
			y = j * step;
			surface[i][j] = f(x, y);
			outFile << surface[i][j] << std::endl;
			lineCount++;
		}
	}

	outFile.close();

	std::ifstream tempFile("output.tmp");
	std::ofstream finalFile("output.txt");
	finalFile << "Line Count: " << lineCount << "\n";
	finalFile << tempFile.rdbuf();

	tempFile.close();
	finalFile.close();
	remove("output.tmp");

	return surface;
	
}

std::vector<float> Task_3::createVertices(const std::vector<std::vector<double>>& surface)
{
	std::vector<float> vertices;
	int rows = surface.size();
	if (rows == 0) return vertices;
	int cols = surface[0].size();

	for(int x = 0; x < rows - 1; ++x){
		for(int y = 0; y < cols - 1; ++y){
			
			vertices.push_back(x);     
            vertices.push_back(y);
            vertices.push_back(surface[x][y]);

            vertices.push_back(x + 1);
            vertices.push_back(y);
            vertices.push_back(surface[x + 1][y]);

            vertices.push_back(x);     
            vertices.push_back(y + 1);
            vertices.push_back(surface[x][y + 1]);

            
            vertices.push_back(x + 1); 
            vertices.push_back(y);
            vertices.push_back(surface[x + 1][y]);

            vertices.push_back(x + 1); 
            vertices.push_back(y + 1);
            vertices.push_back(surface[x + 1][y + 1]);

            vertices.push_back(x);     
            vertices.push_back(y + 1);
            vertices.push_back(surface[x][y + 1]);
		}

	}

	for(int x = 0; x < rows - 1; ++x) {
       for(int y = 0; y < cols - 1; ++y) {
           float z = surface[x][y];

           vertices.push_back(x);     
           vertices.push_back(y);
           vertices.push_back(z);

           vertices.push_back(x / (float)rows);  // R
           vertices.push_back(y / (float)cols);  // G
           vertices.push_back(z / 10.0f);        // B

        }
    }

	return vertices;
}
