#include "rects.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <functional>
#include <iostream>

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
		goMotion(system.rects, elapsedTime, 1);
		rotateItems(system.rects, elapsedTime, 0);
	};
	system.behaviors[1].onUpdate = [&](float elapsedTime) {
		straightTurn(system.rects, elapsedTime, 0);
	};
	system.behaviors[2].onUpdate = [&](float elapsedTime) {
		goMotion(system.rects, elapsedTime, 1);
		goMotion(system.rects, elapsedTime, 3);
		transparencyChenge(system.rects, elapsedTime, 0);
	};
	system.behaviors[3].onUpdate = [&](float elapsedTime) {
		straightTurn(system.rects, elapsedTime, 1);
	};
	system.behaviors[4].onUpdate = [&](float elapsedTime) {
		goMotion(system.rects, elapsedTime, 0);
		deformation(system.rects, elapsedTime, 0);
	}; 
	system.behaviors[5].onUpdate = [&](float elapsedTime) {
		straightTurn(system.rects, elapsedTime, 0);
		rotateItems(system.rects, elapsedTime, 1);
	};
	system.behaviors[6].onUpdate = [&](float elapsedTime) {
		goMotion(system.rects, elapsedTime, 0);
		goMotion(system.rects, elapsedTime, 3);
		deformation(system.rects, elapsedTime, 1);
		rotateItems(system.rects, elapsedTime, 0);
	};
	system.behaviors[7].onUpdate = [&](float elapsedTime) {
		goMotion(system.rects, elapsedTime, 2);
		straightTurn(system.rects, elapsedTime, 1);
	};
	system.behaviors[8].onUpdate = [&](float elapsedTime) {
		rotateItems(system.rects, elapsedTime, 1);
	};
	system.behaviors[9].onUpdate = [&](float elapsedTime) {
		goMotion(system.rects, elapsedTime, 2);
		transparencyChenge(system.rects, elapsedTime, 1);
	};
}

void initGameSystem(GameSystem &system)
{
	initRects(system.rects);
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
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Animate Rects", sf::Style::Titlebar + sf::Style::Close, settings);
	window.setKeyRepeatEnabled(false);

	GameSystem animateRects;
	initGameSystem(animateRects);

	enterGameLoop(animateRects, window);

	return 0;
}