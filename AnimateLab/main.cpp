#include "rects.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <array>

typedef std::function<void(float dt)> GameBehavior;

struct GameSystem
{
	sf::Clock clock;
	float time;
	Rects rects;
	std::array<GameBehavior, 10> behaviors;
	int currentBehaviorIndex;
};

void initBehaviors(GameSystem &system)
{
	system.behaviors = { 
		[&](float elapsedTime) {
			goMotion(system.rects, elapsedTime, 1);
			rotateItems(system.rects, elapsedTime, 0);
		},
		[&](float elapsedTime) {
			straightTurn(system.rects, elapsedTime, 0);
		},
		[&](float elapsedTime) {
			goMotion(system.rects, elapsedTime, 1);
			goMotion(system.rects, elapsedTime, 3);
			transparencyChenge(system.rects, elapsedTime, 0);
		},
		[&](float elapsedTime) {
			straightTurn(system.rects, elapsedTime, 1);
		},
		[&](float elapsedTime) {
			goMotion(system.rects, elapsedTime, 0);
			deformation(system.rects, elapsedTime, 0);
		},
		[&](float elapsedTime) {
			straightTurn(system.rects, elapsedTime, 0);
			rotateItems(system.rects, elapsedTime, 1);
		},
		[&](float elapsedTime) {
			goMotion(system.rects, elapsedTime, 0);
			goMotion(system.rects, elapsedTime, 3);
			deformation(system.rects, elapsedTime, 1);
			rotateItems(system.rects, elapsedTime, 0);
		},
		[&](float elapsedTime) {
			goMotion(system.rects, elapsedTime, 2);
			straightTurn(system.rects, elapsedTime, 1);
		},
		[&](float elapsedTime) {
			rotateItems(system.rects, elapsedTime, 1);
		},
		[&](float elapsedTime) {
			goMotion(system.rects, elapsedTime, 2);
			transparencyChenge(system.rects, elapsedTime, 1);
		}
	};
}

void initGameSystem(GameSystem &system)
{
	initRects(system.rects);
	initBehaviors(system);
	system.time = 0;
	system.currentBehaviorIndex = 0;
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

	system.clock.restart();
	system.time += elapsedTime;

	if (system.time >= TIME_FOR_ONE_ANIMATE)
	{
		system.currentBehaviorIndex++;
		system.time = 0;
		if (system.currentBehaviorIndex == arrSize)
			system.currentBehaviorIndex = 0;
	}

	system.behaviors[system.currentBehaviorIndex](elapsedTime);
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
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Animate Rects", sf::Style::Titlebar + sf::Style::Close, settings);
	window.setKeyRepeatEnabled(false);

	GameSystem animateRects;
	initGameSystem(animateRects);

	enterGameLoop(animateRects, window);

	return 0;
}