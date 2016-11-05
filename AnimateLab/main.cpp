#include <SFML/Graphics.hpp>
#include "rects.h"
#include <ctime>
#include <functional>
#include <queue>
#include <iostream>

static const int RESOLUTION_W = 1024;
static const int RESOLUTION_H = 720;

static const sf::Color BACKGROUND_COLOR = sf::Color(253, 253, 253);

static const float TIME_FOR_ONE_ANIMATE = 1.5;
static const float MOV_LENGTH = 300;
static const float CHENGING_ALPHA_SPEED = 325;

struct GameBehavior
{
	std::function<void(float dt)> onUpdate;
};

struct GameSystem
{
	sf::Clock clock;
	float time;
	Rects rects;
	GameBehavior behaviors[10];
	int currentBehavior;
};


void initBehaviors(GameSystem &system)
{
	system.behaviors[0].onUpdate = [&](float elapsedTime) {
		goLeft(system.rects, elapsedTime);
		rotateItemsClockwise(system.rects, elapsedTime);
	};
	system.behaviors[1].onUpdate = [&](float elapsedTime) {
		rotateRectSystemClockwise(system.rects, elapsedTime);
	};
	system.behaviors[2].onUpdate = [&](float elapsedTime) {
		goLeft(system.rects, elapsedTime);
		goDown(system.rects, elapsedTime);
		// colorAnimate
	};
	system.behaviors[3].onUpdate = [&](float elapsedTime) {
		rotateRectSystemCounterclockwise(system.rects, elapsedTime);
	};
	system.behaviors[4].onUpdate = [&](float elapsedTime) {
		goRight(system.rects, elapsedTime);
		compression(system.rects, elapsedTime);
	}; 
	system.behaviors[5].onUpdate = [&](float elapsedTime) {
		rotateRectSystemClockwise(system.rects, elapsedTime);
		rotateItemsCounterclockwise(system.rects, elapsedTime);
	};
	system.behaviors[6].onUpdate = [&](float elapsedTime) {
		goRight(system.rects, elapsedTime);
		goDown(system.rects, elapsedTime);
		expansion(system.rects, elapsedTime);
		rotateItemsClockwise(system.rects, elapsedTime);
	};
	system.behaviors[7].onUpdate = [&](float elapsedTime) {
		goUp(system.rects, elapsedTime);
		rotateRectSystemCounterclockwise(system.rects, elapsedTime);
	};
	system.behaviors[8].onUpdate = [&](float elapsedTime) {
		rotateItemsCounterclockwise(system.rects, elapsedTime);
	};
	system.behaviors[9].onUpdate = [&](float elapsedTime) {
		goUp(system.rects, elapsedTime);
	};
}

void initGameSystem(GameSystem &system)
{
	initRects(system.rects, TIME_FOR_ONE_ANIMATE);
	initBehaviors(system);
	system.time = 0;
	system.currentBehavior = 0;
}

void handleEvents(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}

void update(GameSystem &system)
{
	const float arrSize = sizeof(system.behaviors) / sizeof(system.behaviors[0]);
	const float elapsedTime = system.clock.getElapsedTime().asSeconds();
	std::cout << elapsedTime << "\n";
	system.clock.restart();
	system.time += elapsedTime;

	if (system.time >= TIME_FOR_ONE_ANIMATE)
	{
		system.currentBehavior++;
		system.time = 0;
		if (system.currentBehavior == arrSize)
			system.currentBehavior = 0;
	}

	system.behaviors[system.currentBehavior].onUpdate(elapsedTime);
}

void render(GameSystem &system, sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	drawRects(window, system.rects);
	window.display();
}

void enterGameLoop(GameSystem &system, sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		handleEvents(window);
		update(system);
		render(system, window);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Animate Rects", sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	GameSystem animateRects;
	initGameSystem(animateRects);

	enterGameLoop(animateRects, window);
	
	return 0;
}