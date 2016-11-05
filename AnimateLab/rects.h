#pragma once
#include <SFML/Graphics.hpp>

struct Rects
{
	static const size_t CAPACITY = 6;
	float animateTime;

	size_t SIZE;
	sf::RectangleShape items[CAPACITY];
};

void initRects(Rects &rects, const float &animateTime);

void drawRects(sf::RenderWindow &window, Rects &rects);

void goRight(Rects &rects, const float &elapsedTime);
void goLeft(Rects &rects, const float &elapsedTime);
void goUp(Rects &rects, const float &elapsedTime);
void goDown(Rects &rects, const float &elapsedTime);

void compression(Rects &rects, const float &elapsedTime);
void expansion(Rects &rects, const float &elapsedTime);

void rotateItemsClockwise(Rects &rects, const float &elapsedTime);
void rotateItemsCounterclockwise(Rects &rects, const float &elapsedTime);

void rotateRectSystemClockwise(Rects &rects, const float &elapsedTime);
void rotateRectSystemCounterclockwise(Rects &rects, const float &elapsedTime);