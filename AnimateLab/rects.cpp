#include "rects.h"
#include "constants.h"
#include <iostream>

void initRects(Rects &rects)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		rects.items[itemNumber].setSize({ RECT_SIDE_SIZE , RECT_SIDE_SIZE });
		rects.items[itemNumber].setOrigin({ RECT_SIDE_SIZE / 2.0 , RECT_SIDE_SIZE / 2.0 });
		rects.items[itemNumber].setPosition(START_POS.x + RECT_SIDE_SIZE / 2.0, START_POS.y + itemNumber * (RECT_SIDE_SIZE + RECT_MARGIN) + RECT_SIDE_SIZE / 2.0);
		rects.items[itemNumber].setFillColor(RECT_START_COLOR);
	}
	rects.alphaChenge = 0;
}

void drawRects(sf::RenderWindow &window, Rects &rects)
{
	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		window.draw(rects.items[itemNumber]);
}

void goMotion(Rects &rects, const float &elapsedTime, int mode) // mode 0/1/2/3 == right/left/up/down
{
	const float axialMovement = elapsedTime * MOVE_LENGTH;
	sf::Vector2f movement = { 0, 0 };

	if (mode == 0)
		movement = { axialMovement, 0 };
	if (mode == 1)
			movement = { -axialMovement, 0 };
	if (mode == 2)
			movement = { 0, -axialMovement };
	if (mode == 3)
			movement = { 0, axialMovement };

	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
		rects.items[itemNumber].move(movement);
}

void deformation(Rects &rects, const float &elapsedTime, int mode) // mode 0/1 == compression/expansion
{
	sf::RectangleShape *rect;
	float verticalDeformation = RECT_SIDE_SIZE;

	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		rect = &rects.items[itemNumber];

		if (mode == 0)
			verticalDeformation = rect->getSize().y - DEFORMATION * elapsedTime / TIME_FOR_ONE_ANIMATE;
		if (mode == 1)
			verticalDeformation = rect->getSize().y + DEFORMATION * elapsedTime / TIME_FOR_ONE_ANIMATE;

		rect->setSize({ RECT_SIDE_SIZE , verticalDeformation });
	}
}

void rotateItems(Rects &rects, const float &elapsedTime, int mode) // mode 0/1 == clockwise/counterclockwise
{
	sf::RectangleShape *rect;
	float rotation = 0;

	if (mode == 0)
		rotation = ITEM_ROTATE_ANGLE / TIME_FOR_ONE_ANIMATE * elapsedTime;
	if (mode == 1)
		rotation = (-1) * ITEM_ROTATE_ANGLE / TIME_FOR_ONE_ANIMATE * elapsedTime;

	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		rect = &rects.items[itemNumber];
		rect->rotate(rotation);
	}	
}

void straightTurn(Rects &rects, const float &elapsedTime, int mode) // mode 0/1 == clockwise/counterclockwise
{
	sf::RectangleShape *rect;
	float rotation = 0;
	const float itemsCount = sizeof(rects.items) / sizeof(rect);
	sf::Vector2f movementVector = { 0, 0 };

	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		rect = &rects.items[itemNumber];
		const float diagonalMov = elapsedTime * (RADIUS_COEFFICIENT - itemNumber) * ((RECT_SIDE_SIZE + RECT_MARGIN) / TIME_FOR_ONE_ANIMATE);

		if (mode == 0)
			movementVector = { diagonalMov, diagonalMov };
		if (mode == 1)
			movementVector = { -diagonalMov, -diagonalMov };

		rect->move(movementVector);
	}
}

void transparencyChenge(Rects &rects, const float &elapsedTime, int mode) // mode 0/1 == increase/reduce
{
	sf::RectangleShape *rect;
	sf::Uint8 newAlpha = 255;

	rects.alphaChenge += (elapsedTime * TRANSPARENCY_CHENGE / TIME_FOR_ONE_ANIMATE);

	for (size_t itemNumber = 0; itemNumber < rects.CAPACITY; itemNumber++)
	{
		rect = &rects.items[itemNumber];

		if (mode == 0)
			newAlpha = RECT_START_COLOR.a - static_cast<sf::Uint8>(rects.alphaChenge);
		if (mode == 1)
			newAlpha = RECT_START_COLOR.a - static_cast<sf::Uint8>(TRANSPARENCY_CHENGE) + static_cast<sf::Uint8>(rects.alphaChenge);

		rect->setFillColor(sf::Color(RECT_START_COLOR.r, RECT_START_COLOR.g, RECT_START_COLOR.b, newAlpha));
	}

	if (rects.alphaChenge >= TRANSPARENCY_CHENGE)
		rects.alphaChenge = 0;
}