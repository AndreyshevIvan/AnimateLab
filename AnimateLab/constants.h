#pragma once

const int RESOLUTION_W = 1024;
const int RESOLUTION_H = 720;

const float RECT_SIDE_SIZE = 40;
const float RECT_MARGIN = 10;
const sf::Vector2f START_POS = { RESOLUTION_W / 2.0f, RESOLUTION_H / 5.0f };
const sf::Color RECT_START_COLOR = sf::Color(102, 0, 102, 255);

const float TIME_FOR_ONE_ANIMATE = 1.5;

const float MOVE_LENGTH = 100;
const float DEFORMATION = RECT_SIDE_SIZE / 2.0f;
const float ITEM_ROTATE_ANGLE = 90;
const float TRANSPARENCY_CHENGE = 100;
const float RADIUS_COEFFICIENT = 2.5;

static const sf::Color BACKGROUND_COLOR = sf::Color(253, 253, 253);