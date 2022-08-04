#pragma once
#include "Macros.h"
#include "Tile.h"
#include "Cat.h"
#include "Bfs.h"
#include <vector>


class Board {
public:
	Board(const int level);
	~Board();

	void draw(sf::RenderWindow& window);
	void handleClick(sf::Vector2f& location);
	void press(const sf::Vector2f& location, sf::RenderWindow& window);
	void drawMessage(const std::string& message, sf::RenderWindow& window);
	void resetScreen(const int level);
	bool getAnimation() const;
	void setAnimation(const bool status);
	
private:
	void initBoard();
	void updateCat(sf::RenderWindow& window);
	void initLevel(Level);
	void markTiles(const int difficulty);
	void initMessage();
	sf::Vector2f findPath();

	std::vector<std::vector <Tile*>> m_tiles;
	std::map<std::string, sf::Text> m_message;
	Cat m_cat;
	int m_steps;
	int m_level;
	bool m_animation;
};
