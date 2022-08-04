#pragma once

#include <SFML/Graphics.hpp>

const float WIN_W = 800;
const float WIN_H = 800;
const int RADIUS = 30;
const std::string FONT_PATH = "C:/Windows/Fonts/Arial.ttf";
const std::string CAT = "cat1.png";

const int EASY = 13;
const int MEDIUM = 10;
const int HARD = 5;

enum class Top
{
	First = 10,
	Middle = 122,
	Last = 234,
};

enum class Way
{
	Regular = 1,
	Reverse = -1,
};

enum Direction
{
	Left,
	Right,
	Top_Left,
	Top_Right,
	Bottom_Left,
	Bottom_Right,
};

enum Level
{
	Easy,
	Medium,
	Hard,
};


