#pragma once
#include <SFML/Graphics.hpp>

struct Rects
{
	static const size_t CAPACITY = 6;
	float alphaChenge;

	size_t SIZE;
	sf::RectangleShape items[CAPACITY];
};

void initRects(Rects &rects);

void drawRects(sf::RenderWindow &window, Rects &rects);

void goMotion(Rects &rects, const float &elapsedTime, int mode); // mode 0/1/2/3 == right/left/up/down
void deformation(Rects &rects, const float &elapsedTime, int mode); // mode 0/1 == compression/expansion
void rotateItems(Rects &rects, const float &elapsedTime, int mode); // mode 0/1 == clockwise/counterclockwise
void straightTurn(Rects &rects, const float &elapsedTime, int mode); // mode 0/1 == clockwise/counterclockwise
void transparencyChenge(Rects &rects, const float &elapsedTime, int mode); // mode 0/1 == increase/reduce