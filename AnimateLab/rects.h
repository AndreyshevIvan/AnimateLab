#pragma once
#include <SFML/Graphics.hpp>

struct Shapes
{
	static const size_t CAPACITY = 6;
	float moveing;

	size_t SIZE;
	sf::RectangleShape items[CAPACITY];
};

void initializeRects(Shapes &shapes);
void drawRects(sf::RenderWindow &window, Shapes &shapes);
void firstMov(Shapes &myShapes);
void secondMov(Shapes &myShapes);
void thirdMov(Shapes &myShapes);