#include "rects.h"

static const float SHAPE_SIDE_SIZE = 40;
static const sf::Vector2f START_POS = { 0, 0 };
static const sf::Color SHAPE_START_COLOR = sf::Color(102, 0, 102, 255);
static const float SHAPES_MARGIN = 10;

void initializeRects(Shapes &myShapes)
{
	for (size_t itemNumber = 0; itemNumber < myShapes.CAPACITY; itemNumber++)
	{
		myShapes.items[itemNumber].setSize({ SHAPE_SIDE_SIZE , SHAPE_SIDE_SIZE });
		myShapes.items[itemNumber].setOrigin({ SHAPE_SIDE_SIZE / 2.0 , SHAPE_SIDE_SIZE / 2.0 });
		myShapes.items[itemNumber].setPosition(0, itemNumber * (SHAPE_SIDE_SIZE + SHAPES_MARGIN) + SHAPE_SIDE_SIZE / 2.0);
		myShapes.items[itemNumber].setFillColor(SHAPE_START_COLOR);
	}
}

void drawRects(sf::RenderWindow &window, Shapes &myShapes)
{
	for (size_t itemNumber = 0; itemNumber < myShapes.CAPACITY; itemNumber++)
		window.draw(myShapes.items[itemNumber]);
}

void firstMov(Shapes &myShapes)
{
	for (size_t itemNumber = 0; itemNumber < myShapes.CAPACITY; itemNumber++)
		myShapes.items[itemNumber].move(myShapes.moveing, 0);
}

void secondMov(Shapes &myShapes)
{
	for (size_t itemNumber = 0; itemNumber < myShapes.CAPACITY; itemNumber++)
		myShapes.items[itemNumber].move(myShapes.moveing, myShapes.moveing);
}

void thirdMov(Shapes &myShapes)
{
	for (size_t itemNumber = 0; itemNumber < myShapes.CAPACITY; itemNumber++)
		myShapes.items[itemNumber].move(myShapes.moveing, myShapes.moveing);
}