#include <deque>
#include <iostream>
#include <cstdlib>
#include <chrono>

#include "map.h"

// DO NOT USE "using name std" AS WE ARE SHADOWING THE NAME MAP !

int main()
{
	Map map(50, 50);

	map.createNewPoint(12, 12, FIELD_TYPE::WATER);
	map.createNewPoint(5, 4, FIELD_TYPE::TEMPEST);
	map.createNewPoint(6, 6, FIELD_TYPE::REEF);
	map.createNewPoint(7, 5, FIELD_TYPE::REEF);
	map.createNewPoint(7, 6, FIELD_TYPE::OBSTACLE);
	map.createNewPoint(7, 8, FIELD_TYPE::OBSTACLE);
	map.createNewPoint(6, 7, FIELD_TYPE::OBSTACLE);
	map.createNewPoint(6, 5, FIELD_TYPE::REEF);

	std::cout << std::endl << "-------------- LEGEND -------------" << std::endl << std::endl;
	std::cout << ". -> water" << std::endl << "^ -> reef" << std::endl << "Z -> tempest" << std::endl << "X -> obstacle" << std::endl <<
		"S -> starting point" << std::endl << "E -> destination point" << std::endl << "# -> path between S and E" << std::endl;

	std::cout << std::endl << "--------------- MAP ---------------" << std::endl << std::endl;
	map.displayMap();

	std::cout << std::endl << "----------- PATHFINDING -----------" << std::endl << std::endl;
	auto t1 = std::chrono::high_resolution_clock::now();
	map.searchForPath(0, 6, 7, 7);
	auto t2 = std::chrono::high_resolution_clock::now();
	

	std::cout << std::endl << "----------- PERFORMANCE -----------" << std::endl << std::endl;
	std::chrono::duration<double, std::milli> ms_double = t2 - t1;
	std::cout << "It tooks " << ms_double.count() << "ms to find the path." << std::endl;
	std::cout << "Number of nodes explored: " << map.getFastestPathNodes() << std::endl;

	return 0;
}
