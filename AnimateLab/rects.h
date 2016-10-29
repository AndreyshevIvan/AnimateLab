#pragma once
#include <SFML/Graphics.hpp>

static const int SHAPES_COUNT = 6;

struct ArrayOfRects
{
	sf::RectangleShape shape[SHAPES_COUNT];
};

void initializeRects(ArrayOfRects &myRects);
void drawRects(sf::RenderWindow &window, ArrayOfRects &myRects);
