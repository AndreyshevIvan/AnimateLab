#include <SFML/Graphics.hpp>
#include "rects.h"
#include <functional>
#include <ctime>
#include <queue>
#include <iostream>

static const int RESOLUTION_W = 1024;
static const int RESOLUTION_H = 720;

static const sf::Color BACKGROUND_COLOR = sf::Color(253, 253, 253);

static const float MOV_LENGTH = 300;
static const float MOVSPEED = 120;
static const float CHENGING_ALPHA_SPEED = 325;

struct Timer
{
	float GetElapsedSeconds()const
	{
		return 0.001f * clock.getElapsedTime().asMilliseconds();
	}

	void Restart()
	{
		clock.restart();
	}

	sf::Clock clock;
	float timeLeft;
};

void handleEvents(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}

void update(Timer &timer, Shapes &myShapes)
{
	float elapsedTime = timer.GetElapsedSeconds();
	timer.Restart();
	timer.timeLeft += elapsedTime;
	myShapes.moveing = elapsedTime * MOVSPEED;
	myShapes.chengeAlpha = elapsedTime * CHENGING_ALPHA_SPEED;

	if (timer.timeLeft <= 2.0f)
		firstMov(myShapes);

	if (timer.timeLeft > 2.0f && timer.timeLeft <= 4.0f)
		secondMov(myShapes);

	//if (timer.timeLeft > 4.0f && timer.timeLeft <= 6.0f)
	//	thirdMov(myShapes);
}

void render(sf::RenderWindow &window, Shapes &myShapes)
{
	window.clear(BACKGROUND_COLOR);
	drawRects(window, myShapes);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Animation", sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	Timer timer;
	timer.timeLeft = 0;
	Shapes myShapes;

	initializeRects(myShapes);

	while (window.isOpen())
	{
		handleEvents(window);
		update(timer, myShapes);
		render(window, myShapes);
	}

	return 0;
}