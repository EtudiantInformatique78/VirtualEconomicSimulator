#include "map.h"
#include "SFML/Graphics.hpp"

Map::Map(int _xSize, int _ySize) : fastestPathNodes(0)
{
	std::deque<Point> initialPoint;
	initialPoint.push_back(Point(0, 0));
	board.push_back(initialPoint);

	generateMapUsingPerlin();

	smallestX = 0;
	greatestX = 0;
	smallestY = 0;
	greatestY = 0;

	for (int i = 0; i != _ySize; ++i)
	{
		createNewLine(COORDINATE_DIRECTION::POSITIVE);
	}
	for (int i = 0; i != _xSize; ++i)
	{
		createNewColumn(COORDINATE_DIRECTION::POSITIVE);
	}

	//Initialise fieldTypeInformations
	fieldTypeInformations = 
	{
		{ FIELD_TYPE::OBSTACLE, std::make_pair<char, double>('X', 0) },
		{ FIELD_TYPE::ETP    , std::make_pair<char, double>('O', 1) },
		{ FIELD_TYPE::GRASSLAND , std::make_pair<char, double>('.', 1.1) },
		{ FIELD_TYPE::WATER   , std::make_pair<char, double>('w', 1.5) },
		{ FIELD_TYPE::MOUNTAIN   , std::make_pair<char, double>('^', 1.4) },
		{ FIELD_TYPE::FOREST   , std::make_pair<char, double>('T', 1.3) },
		{ FIELD_TYPE::BEACH   , std::make_pair<char, double>('T', 1.2) },
		{ FIELD_TYPE::PATH   , std::make_pair<char, double>('T', 1) }
	};
}

Map::~Map()
{
}

// Is the point is in the path found ?
bool Map::isInPath(Node* finalNode, const Point& cell) const
{
	while (finalNode != NULL)
	{
		if (finalNode->getPoint()->getX() == cell.getX() && finalNode->getPoint()->getY() == cell.getY())
		{
			return true;
		}
		finalNode = finalNode->getParent();
	}
	return false;
}

// Add a new column to the map
void Map::createNewColumn(COORDINATE_DIRECTION direction)
{
	int yCoordinate = smallestY;
	int totalYSize = greatestY + abs(smallestY);
	if (direction == COORDINATE_DIRECTION::POSITIVE)
	{
		greatestX += 1;
		for (int i = 0; i != totalYSize + 1; ++i)
		{
			board[i].push_back(Point(greatestX, yCoordinate++));
		}

	}
	if (direction == COORDINATE_DIRECTION::NEGATIVE)
	{
		smallestX -= 1;
		for (int i = 0; i != totalYSize + 1; ++i)
		{
			board[i].push_front(Point(smallestX, yCoordinate++));
		}
	}
}

// Add a new line to the map
void Map::createNewLine(COORDINATE_DIRECTION direction)
{
	std::deque<Point> line;
	int xCoordinate = smallestX;
	int totalXSize = greatestX + abs(smallestX);

	if (direction == COORDINATE_DIRECTION::POSITIVE)
	{
		greatestY += 1;
		for (int i = 0; i != totalXSize + 1; ++i)
		{
			line.push_back(Point(xCoordinate++, greatestY));
		}
		board.push_back(line);
	}
	else if (direction == COORDINATE_DIRECTION::NEGATIVE)
	{
		smallestY -= 1;
		for (int i = 0; i != totalXSize + 1; ++i)
		{
			line.push_back(Point(xCoordinate++, smallestY));
		}
		board.push_front(line);
	}
}

// Get the point from the map at the given coordinates
Point* Map::getPoint(int x, int y)
{
	for (int i = 0; i != board.size(); ++i)
	{
		if (board[i][0].getY() == y)
		{
			for (int j = 0; j != board[i].size(); ++j)
			{
				if (board[i][j].getX() == x)
				{
					return &board[i][j];
				}
			}
		}
	}
	return NULL;
}

// Create a new point in the map. If it is currenlty oustide the boundaries of the "known" map, expand it until the point can be placed.
void Map::createNewPoint(int x, int y, FIELD_TYPE fieldType)
{
	// If point already exists, only update type
	if (y <= greatestY && y >= smallestY && x <= greatestX && x >= smallestX)
	{
		if ((getPoint(x, y)->getFieldType() == FIELD_TYPE::OBSTACLE && fieldType == FIELD_TYPE::ETP) || (getPoint(x, y)->getFieldType() == FIELD_TYPE::ETP && fieldType == FIELD_TYPE::ETP))
		{
			createNewPoint(x = rand() % greatestX, y = rand() % greatestY, fieldType);
			return;
		}
		else
		{
			getPoint(x, y)->setFieldType(fieldType);
			return;
		}
		
	}

	// extend map on x negative coordinates
	if (x < 0)
	{
		for (int i = abs(smallestX); i < abs(x); ++i)
		{
			createNewColumn(COORDINATE_DIRECTION::NEGATIVE);
		}
	}
	// extend map on x positive coordinates
	else
	{
		for (int i = greatestX; i < x; ++i)
		{
			createNewColumn(COORDINATE_DIRECTION::POSITIVE);
		}
	}

	// extend map on y negative coordinates
	if (y < 0)
	{
		for (int i = abs(smallestY); i < abs(y); ++i)
		{
			createNewLine(COORDINATE_DIRECTION::NEGATIVE);
		}
	}
	// extend map on y positive coordinates
	else
	{
		for (int i = greatestY; i < y; ++i)
		{
			createNewLine(COORDINATE_DIRECTION::POSITIVE);
		}
	}

	// Set field type to the right cell
	getPoint(x, y)->setFieldType(fieldType);
}

// Get the distance between to point
double Map::getDistanceBetweenTwoPoint(int x1, int y1, int x2, int y2) const
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Get element with the lowest fCost
std::shared_ptr<Node> Map::getLowestFCostIndex(const std::unordered_map<std::string, std::shared_ptr<Node>>& list) const
{
	std::shared_ptr<Node> smallestCost = list.begin()->second;
	for (auto it = list.begin(); it != list.end(); it++) 
	{
		if (smallestCost->getFCost() > it->second->getFCost())
		{
			smallestCost = it->second;
		}
	}
	return smallestCost;
}

// Is the point given as parameter are in the map ?
bool Map::isStartAndDestinationPointOnTheMap(int startingX, int startingY, int destinationX, int destinationY) const
{
	// check starting coordinate
	if (startingY > greatestY || startingY < smallestY || startingX > greatestX || startingX < smallestX)
	{
		return false;
	}

	// check destination coordinate
	if (destinationY > greatestY || destinationY < smallestY || destinationX > greatestX || destinationX < smallestX)
	{
		return false;
	}
	return true;
}

// Implementation of the A* algorithm to find a path between the two coordinates
void Map::searchForPath(int startingX, int startingY, int destinationX, int destinationY)
{
	// If starting point or destination point are not in the current map, stop execution
	if (!isStartAndDestinationPointOnTheMap(startingX, startingY, destinationX, destinationY))
	{
		std::cout << "The starting or destination point are out of the map ! The path will not be searched." << std::endl;
		return;
	}

	// We choose unordered map for fast access to elements, easy insert / delete anywhere in the list, as they are not contiguous in memory
	// Open list store node to inspect
	std::unordered_map<std::string, std::shared_ptr<Node>> openList;
	// Close list store explored nodes
	std::unordered_map<std::string, std::shared_ptr<Node>> closeList;
	// Key in the maps above are formated like : "x-coordinate;y-coordinate"

	openList.clear();

	//Add start node to openList
	const std::shared_ptr<Node> startNode(new Node(getPoint(startingX, startingY)));
	openList.insert({ std::to_string(startNode->getPoint()->getX()) + ';' + std::to_string(startNode->getPoint()->getY()) , startNode });

	while (openList.size() > 0)
	{
		// Move lowest cost from open to close list
		const std::shared_ptr<Node> currentNode = getLowestFCostIndex(openList);
		const std::string currentNodeKey = std::to_string(currentNode->getPoint()->getX()) + ';' + std::to_string(currentNode->getPoint()->getY());
		closeList.insert({ currentNodeKey, currentNode });
		openList.erase(currentNodeKey);

		// Win condition
		if (currentNode->getPoint()->getX() == destinationX && currentNode->getPoint()->getY() == destinationY)
		{
			fastestPathNodes = 0;

			if (currentNode->getPoint()->getX() == destinationX && currentNode->getPoint()->getY() == destinationY)
			{
				// Mettez à jour le nombre de nœuds explorés dans le chemin le plus rapide
				fastestPathNodes = 0;  // Réinitialisez le compteur pour le chemin le plus rapide

				// Tracez le chemin et comptez les nœuds explorés
				Node* pathNode = currentNode.get();   // Utilisez une variable temporaire
				while (pathNode != nullptr)
				{
					fastestPathNodes++;
					if (pathNode->getPoint()->getX() != startingX && pathNode->getPoint()->getY() != startingY && pathNode->getPoint()->getX() != destinationX && pathNode->getPoint()->getY() != destinationY)
					{
						pathNode->getPoint()->setFieldType(FIELD_TYPE::PATH);
					}
					pathNode = pathNode->getParent();
				}

				// Inversez le chemin pour obtenir le bon ordre
				fastestPathNodes--;
			}
		}

		// Get all the 8 adjacentes nodes
		std::vector<Node> adjacentNodes = 
		{
			Node(getPoint(currentNode->getPoint()->getX()    , currentNode->getPoint()->getY() + 1)),
			Node(getPoint(currentNode->getPoint()->getX() + 1, currentNode->getPoint()->getY() + 1)),
			Node(getPoint(currentNode->getPoint()->getX() + 1, currentNode->getPoint()->getY())),
			Node(getPoint(currentNode->getPoint()->getX() + 1, currentNode->getPoint()->getY() - 1)),
			Node(getPoint(currentNode->getPoint()->getX()	 , currentNode->getPoint()->getY() - 1)),
			Node(getPoint(currentNode->getPoint()->getX() - 1, currentNode->getPoint()->getY() - 1)),
			Node(getPoint(currentNode->getPoint()->getX() - 1, currentNode->getPoint()->getY())),
			Node(getPoint(currentNode->getPoint()->getX() - 1, currentNode->getPoint()->getY() + 1))
		};

		// explore adjacentes nodes
		for (int i = 0; i != adjacentNodes.size(); ++i)
		{
			// Node does not exists on the map
			if (adjacentNodes[i].getPoint() == NULL)
			{
				continue;
			}

			/*
			* adjacenteNodes vector is filled by nodes as follow: top, top right,right, bottom right, bottom, bottom left, left, top left
			* With vector index, each odd index represents a diagonal.
			* For each diagonal, we check if the nodes with index-1 and index+1 are obstacle, and if it is the case we do not consider the node, as we can't follow the diagonal of an obstacle
			*/
			// If it is a diagonal
			if (i % 2 != 0)
			{
				// Loop the vector: in the map, the last element is next to the first
				const int nextNodeIndex = (i + 1) % 8;
				const int previousNodeIndex = i - 1;
				if (adjacentNodes[nextNodeIndex].getPoint()->getFieldType() == FIELD_TYPE::OBSTACLE || adjacentNodes[previousNodeIndex].getPoint()->getFieldType() == FIELD_TYPE::OBSTACLE)
				{
					continue;
				}
			}

			const std::string nodeKey = std::to_string(adjacentNodes[i].getPoint()->getX()) + ';' + std::to_string(adjacentNodes[i].getPoint()->getY());
			const auto& nodeInOpenList = openList.find(nodeKey);
			if (
				adjacentNodes[i].getPoint()->getFieldType() == FIELD_TYPE::OBSTACLE || // If it is an obstacle
				closeList.find(nodeKey) != closeList.end() || // If it exists in the close list
				(nodeInOpenList != openList.end() && nodeInOpenList->second->getFCost() < adjacentNodes[i].getFCost()) //If it exists in the open list with a smaller fCost value
				)
			{
				continue;
			}

			// Create a new node and insert it in the open list
			const double fieldModifier = fieldTypeInformations[adjacentNodes[i].getPoint()->getFieldType()].second;
			const double distanceBetweenAdjacenteNodeAndCurrentNode = getDistanceBetweenTwoPoint(adjacentNodes[i].getPoint()->getX(), adjacentNodes[i].getPoint()->getY(), currentNode->getPoint()->getX(), currentNode->getPoint()->getY());
			const double distanceWithStart = currentNode->getDistanceWithStart() + distanceBetweenAdjacenteNodeAndCurrentNode;
			const double fCost = (distanceWithStart + getDistanceBetweenTwoPoint(adjacentNodes[i].getPoint()->getX(), adjacentNodes[i].getPoint()->getY(), destinationX, destinationY)) * fieldModifier;
			// About currentNode.get() : shared_ptr are stored until the end of the function, so there is no risk of pointer invalidation
			// We need to work with raw pointer here to avoid circular dependencies, and as the value can be intialized with NULL, we didn't want to use weak_ptr, as we know the pointer won't expire
			const std::shared_ptr<Node> node = std::make_shared<Node>(Node(adjacentNodes[i].getPoint(), currentNode.get(), fCost, distanceWithStart));
			openList.insert({ std::to_string(node->getPoint()->getX()) + ';' + std::to_string(node->getPoint()->getY()) , node });

		}
	}
}

void Map::generateMapUsingPerlin()
{
	srand(time(NULL));
	float freq1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - 1)));
	float amp1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - 1)));
	int roundNumber = rand() % 20 + 8;

	for (int x = 0; x < board.size(); ++x)
	{
		for (int y = 0; y < board[x].size(); ++y)
		{
			float perlinValue = 0;

			float freq = freq1;
			float amp = amp1;

			for (int i = 0; i < roundNumber; i++)
			{
				perlinValue += perlin(x * freq / board.size(),y * freq / board.size()) * amp;

				freq *= 2;
				amp /= 2;

			}
			// Contrast
			perlinValue *= 1.2;

			// Clipping
			if (perlinValue > 1.0f)
				perlinValue = 1.0f;
			else if (perlinValue < -1.0f)
				perlinValue = -1.0f;

			int color = (int)(((perlinValue + 1.0f) * 0.5f) * 255);

			// Remappez la valeur de Perlin à la plage de vos types de terrain
			if (color < 20)
			{
				createNewPoint(x, y, FIELD_TYPE::OBSTACLE);
			}
			else if (color >= 20 && color < 80)
			{
				createNewPoint(x, y, FIELD_TYPE::WATER);
			}
			else if (color >= 80 && color < 95)
			{
				createNewPoint(x, y, FIELD_TYPE::BEACH);
			}
			else if (color >= 95 && color < 160)
			{
				createNewPoint(x, y, FIELD_TYPE::GRASSLAND);
			}
			else if (color >= 160 && color < 200)
			{
				createNewPoint(x, y, FIELD_TYPE::FOREST);
			}
			else if (color >= 220 && color < 255)
			{
				createNewPoint(x, y, FIELD_TYPE::MOUNTAIN);
			}
		}
	}
}
void Map::displayMapSFML() const
{
	const int tileSize = 1;  // Ajustez la taille de la tuile en pixels
	sf::RenderWindow window(sf::VideoMode(board.size() * tileSize, board[0].size() * tileSize), "Map");;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (int x = 0; x < board.size(); ++x)
		{
			for (int y = 0; y < board[x].size(); ++y)
			{
				sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
				tile.setPosition(x * tileSize, y * tileSize);

				// Couleur en fonction du type de terrain
				switch (board[x][y].getFieldType())
				{
				case FIELD_TYPE::OBSTACLE:
					tile.setFillColor(sf::Color::Black);
					break;
				case FIELD_TYPE::ETP:
					tile.setFillColor(sf::Color::Magenta);
					break;
				case FIELD_TYPE::GRASSLAND:
					tile.setFillColor(sf::Color::Green);
					break;
				case FIELD_TYPE::WATER:
					tile.setFillColor(sf::Color::Blue);
					break;
				case FIELD_TYPE::BEACH:
					tile.setFillColor(sf::Color::Yellow);
					break;
				case FIELD_TYPE::MOUNTAIN:
					tile.setFillColor(sf::Color(102, 51, 0));  // Brown color for mountains
					break;
				case FIELD_TYPE::FOREST:
					tile.setFillColor(sf::Color(51, 102, 0)); // Dark green for forest
					break;
				case FIELD_TYPE::PATH:
					tile.setFillColor(sf::Color::Red);
					break;
				}
				window.draw(tile);
			}
		}
		window.display();
	}
}
