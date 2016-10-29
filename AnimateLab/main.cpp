#include <SFML/Graphics.hpp>
#include "rects.h"

static const int RESOLUTION_W = 1024;
static const int RESOLUTION_H = 720;

void update(sf::Clock &clock)
{

}

void render(sf::RenderWindow &window, ArrayOfRects &myRects)
{
	drawRects(window, myRects);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_W, RESOLUTION_H), "Animation", sf::Style::Titlebar + sf::Style::Close);
	window.setKeyRepeatEnabled(false);

	ArrayOfRects myRects;
	sf::Clock clock;

	initializeRects(myRects);

	while (window.isOpen())
	{
		update(clock);
		render(window, myRects);
	}

	return 0;
}