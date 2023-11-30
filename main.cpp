#include <deque>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "perlin.h"

int main()
{	
	Map map(1920, 1080);
	
	std::vector<Point> listeEntreprise;
	
	map.generateMapUsingPerlin();

	map.createNewPoint(rand() % 1920, rand() % 1080, FIELD_TYPE::ETP);
	map.createNewPoint(rand() % 1920, rand() % 1080, FIELD_TYPE::ETP);
	map.createNewPoint(rand() % 1920, rand() % 1080, FIELD_TYPE::ETP);
	map.createNewPoint(rand() % 1920, rand() % 1080, FIELD_TYPE::ETP);
	map.createNewPoint(rand() % 1920, rand() % 1080, FIELD_TYPE::ETP);

	//Point coordEntreprise(6, 10, FIELD_TYPE::ETP);
	//Point coordEntreprise2(12, 18, FIELD_TYPE::ETP);
	//Point coordEntreprise3(1, 6, FIELD_TYPE::ETP);
	//Point coordEntreprise4(14, 5, FIELD_TYPE::ETP);
	//Point coordEntreprise5(9, 6, FIELD_TYPE::ETP);
	//
	//listeEntreprise.push_back(coordEntreprise);
	//listeEntreprise.push_back(coordEntreprise2);
	//listeEntreprise.push_back(coordEntreprise3);
	//listeEntreprise.push_back(coordEntreprise4);
	//listeEntreprise.push_back(coordEntreprise5);
	//
	//std::vector<int> distanceEntreprise;

	//for (int i = 0; i < listeEntreprise.size(); i++)
	//{
	//	for  (int j = i + 1; j < listeEntreprise.size(); j++)
	//	{
	//		map.searchForPath(listeEntreprise[i].getX(), listeEntreprise[i].getY(), listeEntreprise[j].getX(), listeEntreprise[j].getY());
	//		std::cout << "Number of nodes explored between: " << listeEntreprise[i].getX() <<","<< listeEntreprise[i].getY() << " and " << listeEntreprise[j].getX() << "," << listeEntreprise[j].getY() << " = " << map.getFastestPathNodes() << std::endl;
	//	}
	//}

	map.displayMapSFML();


	//std::cout << std::endl << "----------- PATHFINDING -----------" << std::endl << std::endl;
	//map.searchForPath(0, 0, 48, 42);

	//std::cout << "Number of nodes explored: " << map.getFastestPathNodes() << std::endl;

	//auto t1 = std::chrono::high_resolution_clock::now();
	//auto t2 = std::chrono::high_resolution_clock::now();

	//std::cout << std::endl << "----------- PERFORMANCE -----------" << std::endl << std::endl;
	//std::chrono::duration<double, std::milli> ms_double = t2 - t1;
	//std::cout << "It tooks " << ms_double.count() << "ms to find the path." << std::endl;
	

	return 0;
}
