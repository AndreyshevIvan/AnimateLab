#include "rects.h"
#include <iostream>

static const int RESOLUTION_W = 1024;
static const int RESOLUTION_H = 720;

static const float RECT_SIDE_SIZE = 40;
static const float RECT_MARGIN = 10;
static const sf::Vector2f START_POS = { RESOLUTION_W / 2.0f, RESOLUTION_H / 5.0f };
static const sf::Color RECT_START_COLOR = sf::Color(102, 0, 102, 255);

static const float MOVE_LENGTH = 100;
static const float COMPRESSION = 10;
static const float ITEM_ROTATE_ANGLE = 90;

void initRects(Rects &rects, const float &animateTime)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		rects.items[itemNumber].setSize({ RECT_SIDE_SIZE , RECT_SIDE_SIZE });
		rects.items[itemNumber].setOrigin({ RECT_SIDE_SIZE / 2.0 , RECT_SIDE_SIZE / 2.0 });
		rects.items[itemNumber].setPosition(START_POS.x + RECT_SIDE_SIZE / 2.0, START_POS.y + itemNumber * (RECT_SIDE_SIZE + RECT_MARGIN) + RECT_SIDE_SIZE / 2.0);
		rects.items[itemNumber].setFillColor(RECT_START_COLOR);
	}
	rects.animateTime = animateTime;
}

void drawRects(sf::RenderWindow &window, Rects &rects)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		window.draw(rects.items[itemNumber]);
}

void goRight(Rects &rects, const float &elapsedTime)
{
	const float movement = elapsedTime * MOVE_LENGTH;
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].move(movement, 0);
}

void goLeft(Rects &rects, const float &elapsedTime)
{
	const float movement = elapsedTime * MOVE_LENGTH;
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].move(-movement, 0);
}

void goUp(Rects &rects, const float &elapsedTime)
{
	const float movement = elapsedTime * MOVE_LENGTH;
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].move(0, -movement);
}

void goDown(Rects &rects, const float &elapsedTime)
{
	const float movement = elapsedTime * MOVE_LENGTH;
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].move(0, movement);
}

void compression(Rects &rects, const float &elapsedTime)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].setSize({ RECT_SIDE_SIZE , rects.items[itemNumber].getSize().y - RECT_SIDE_SIZE / 2.0f * elapsedTime / rects.animateTime });
}

void expansion(Rects &rects, const float &elapsedTime)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].setSize({ RECT_SIDE_SIZE , rects.items[itemNumber].getSize().y + RECT_SIDE_SIZE / 2.0f * elapsedTime / rects.animateTime });
}

void rotateItemsClockwise(Rects &rects, const float &elapsedTime)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].rotate(ITEM_ROTATE_ANGLE / rects.animateTime * elapsedTime);
}

void rotateItemsCounterclockwise(Rects &rects, const float &elapsedTime)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].rotate(-1 * ITEM_ROTATE_ANGLE / rects.animateTime * elapsedTime);
}

void rotateRectSystemClockwise(Rects &rects, const float &elapsedTime)
{
	const float itemsCount = sizeof(rects.items) / sizeof(rects.items[0]);
	const float radiusCoefficient = 2.5; 
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		const float movement = elapsedTime * (radiusCoefficient - itemNumber) * ((RECT_SIDE_SIZE + RECT_MARGIN) / rects.animateTime);
		if (itemNumber < itemsCount / 2)
			rects.items[itemNumber].move(movement, movement);
		else
			rects.items[itemNumber].move(movement, movement);
	}
}

void rotateRectSystemCounterclockwise(Rects &rects, const float &elapsedTime)
{
	const float itemsCount = sizeof(rects.items) / sizeof(rects.items[0]);
	const float radiusCoefficient = 2.5;
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		const float movement = elapsedTime * (radiusCoefficient - itemNumber) * ((RECT_SIDE_SIZE + RECT_MARGIN) / rects.animateTime);
		if (itemNumber < itemsCount / 2)
			rects.items[itemNumber].move(-movement, -movement);
		else
			rects.items[itemNumber].move(-movement, -movement);
	}
}