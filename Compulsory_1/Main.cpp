#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Task_1.h"
#include "Task_2.h"



int main(){


	double number;
	double numOne;
	double numTwo;
	double numThree;
	double numFour;
	double numX;
	double numInterval;

	Task_1 taskOne;
	Task_2 taskTwo;

	std::cout << "For task one: Enter the four numbers in task one in order of the function one by one: ";
	std::cin >> numOne;
	std::cin >> numTwo;
	std::cin >> numThree;
	std::cin >> numFour;
	std::cout << "Now enter the x value for task 1: ";
	std::cin >> numX;

	auto start_Function_One = std::chrono::high_resolution_clock::now();

	taskOne.taskOneFunction(numOne, numTwo, numThree, numFour, numX);

	auto stop_Function_One = std::chrono::high_resolution_clock::now();

	std::cout << "Enter the value of X for task 2 here: ";
	std::cin >> number;

	if(!std::cin) {
		std::cout << "Invalid input!" << std::endl;
		return 1;
	}

	auto start_Function_Two = std::chrono::high_resolution_clock::now();

	taskTwo.taskTwoFunction(number);

	auto stop_Function_Two = std::chrono::high_resolution_clock::now();

	auto duration_Merge_One = std::chrono::duration_cast<std::chrono::milliseconds>(stop_Function_One - start_Function_One);
	std::cout << "\n Time taken for function one: " << duration_Merge_One.count() << " milliseconds" << std::endl;

	auto duration_Merge_Two = std::chrono::duration_cast<std::chrono::milliseconds>(stop_Function_Two - start_Function_Two);
	std::cout << "\n Time taken for function one: " << duration_Merge_Two.count() << " milliseconds" << std::endl;

	std::cout << "Enter the amount of intervals: ";
	std::cin >> numInterval;

	taskTwo.taskTwoInterval(numInterval);

	taskTwo.taskTwoColors(numInterval);

	return 0;
}
