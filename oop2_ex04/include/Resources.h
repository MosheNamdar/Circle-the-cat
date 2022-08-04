#pragma once
#include "Macros.h"
#include "Tile.h"
#include <vector>
#include <iostream>

class Resources
{
public:
	static Resources& instance();

	bool isWonLevel() const;
	bool isLossLevel() const;
	void setWonLevel();
	void setLossLevel();
	void restartLevel();
	void setDirection(const Tile* source, const Tile* destination);
	const sf::Texture& getTexture() const;
	const sf::Font& getFont() const;
	sf::Vector2f getDirection(const Tile* source, const Tile* destination) const;
	const std::vector<sf::Vector2f>& getDirections() const;


private:
	std::vector <sf::Vector2f> m_directions;
	bool m_lossLevel = false;
	bool m_wonLevel = false;
	sf::Texture m_texture;
	sf::Font m_font;

	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
};

sf::Vector2f operator /(const sf::Vector2f&, const int);
bool operator !(const sf::Vector2f&);