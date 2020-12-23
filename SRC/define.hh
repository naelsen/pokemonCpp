#pragma once

#include <SFML/Graphics.hpp>
// 30,30 ---  570,30 ---- 570,570 ------ 30, 600
static const sf::Uint16 WINDOW_WIDTH = 700;
static const sf::Uint16 WINDOW_HEIGHT = 700;
static const sf::Uint16 ARENE_START = 45;
static const sf::Uint16 ARENE_END = 644;
static const sf::Uint16 SIZE_BLOCK = 64;
static const sf::Uint16 SIZE_HEIGHT_PERSO = 64;
static const sf::Uint16 SIZE_WIDTH_PERSO = 64;
static const sf::Uint16 SIZE_BLOCK_POKEBALL = 16;

typedef enum Bg
{
	intro,
	menu,
	choix_personnage,
	choix_covidmon,
	arene
} Bg;