#include "Resources.h"

Resources::Resources()
{
	m_texture.loadFromFile(CAT);
	m_font.loadFromFile(FONT_PATH);
}

Resources& Resources::instance()
{
	static Resources r;
	return r;
}

bool Resources::isWonLevel() const
{
	return m_wonLevel;
}

bool Resources::isLossLevel() const
{
	return m_lossLevel;
}

void Resources::setWonLevel()
{
	m_wonLevel = true;
}

void Resources::setLossLevel()
{
	m_lossLevel = true;
}

void Resources::restartLevel()
{
	m_lossLevel = false;
	m_wonLevel = false;
}

void Resources::setDirection(const Tile* source, const Tile* destination)
{
	m_directions.push_back(getDirection(source, destination));
}

const sf::Texture& Resources::getTexture() const
{
	return m_texture;
}

const sf::Font& Resources::getFont() const
{
	return m_font;
}

sf::Vector2f Resources::getDirection(const Tile* source, const Tile* destination) const
{
	return (destination->getTile().getPosition() - source->getTile().getPosition()) / 9;
}

const std::vector<sf::Vector2f>& Resources::getDirections() const
{
	return m_directions;
}

sf::Vector2f operator/(const sf::Vector2f& coordinate, const int div)
{
	return sf::Vector2f(coordinate.x / div, coordinate.y / div);
}

bool operator!(const sf::Vector2f& coordinate)
{
	return coordinate.x == 0 && coordinate.y == 0;
}
