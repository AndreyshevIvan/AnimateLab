#include "rects.h"
#include <SFML/Graphics.hpp>

static const sf::Vector2f SHAPE_SIZE = { 20, 20 };
static const sf::Vector2f START_POS = { 0, 0 };
static const sf::Color SHAPE_START_COLOR = sf::Color(102, 0, 102, 255);
static const float SHAPES_MARGIN = 10;

void initializeRects(ArrayOfRects &myRects)
{
	auto initArr = myRects.shape;

	for (int rectNumber = 0; sizeof(initArr); rectNumber++)
	{
		initArr[rectNumber] = sf::RectangleShape(SHAPE_SIZE);
		initArr[rectNumber].setFillColor(SHAPE_START_COLOR);
		initArr[rectNumber].setPosition(START_POS.x, (START_POS.y + SHAPE_SIZE.y) * rectNumber);
	}
}

void drawRects(sf::RenderWindow &window, ArrayOfRects &myRects)
{
	auto drawArr = myRects.shape;

	for (int rectNumber = 0; sizeof(drawArr); rectNumber++)
		window.draw(drawArr[rectNumber]);
}