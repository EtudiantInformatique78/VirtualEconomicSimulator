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
	srand(time(NULL));

	int taille = 500;

	Map map(taille, taille);
	
	std::vector<Point> listeEntreprise;

	map.generateMapUsingPerlin();

	for (int i = 0; i < 100; i++)
	{
		int x = rand() % taille;
		int y = rand() % taille;
		map.createNewPoint(x, y, FIELD_TYPE::ETP);
		listeEntreprise.push_back(Point(x,y, FIELD_TYPE::ETP));
	}

	//for (int i = 0; i < listeEntreprise.size(); ++i)
	//{
	//	for  (int j = i + 1; j < listeEntreprise.size(); ++j)
	//	{
	//		map.searchForPath(listeEntreprise[i].getX(), listeEntreprise[i].getY(), listeEntreprise[j].getX(), listeEntreprise[j].getY());
	//		std::cout << "Number of nodes explored between: " << listeEntreprise[i].getX() <<","<< listeEntreprise[i].getY() << " and " << listeEntreprise[j].getX() << "," << listeEntreprise[j].getY() << " = " << map.getFastestPathNodes() << std::endl;
	//	}
	//}

	map.displayMapSFML();

	return 0;
}
