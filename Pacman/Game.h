#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int H = 21;
const int W = 19;
const int ts = 25;
const int score_to_win = 168;
bool game_over = false;

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};
