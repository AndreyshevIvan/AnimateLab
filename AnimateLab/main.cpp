#include <SFML/Graphics.hpp>
#include "rects.h"

static const int RESOLUTION_W = 1024;
static const int RESOLUTION_H = 720;

static const sf::Color BACKGROUND_COLOR = sf::Color(253, 253, 253);

void handleEvents(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}

void update(sf::Clock &clock)
{
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

	Shapes myShapes;
	sf::Clock clock;

	initializeRects(myShapes);

	while (window.isOpen())
	{
		handleEvents(window);
		update(clock);
		render(window, myShapes);
	}

	return 0;
}