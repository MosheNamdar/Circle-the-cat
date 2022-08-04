#include "Tile.h"

Tile::Tile(const sf::Vector2f& position)
{
	m_tile.setRadius(RADIUS);
	m_tile.setFillColor(sf::Color::Green);
	m_tile.setPosition(position);
	m_tile.setOrigin(m_tile.getRadius(), m_tile.getRadius());
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(m_tile);
}

sf::FloatRect Tile::getGlobalBounds()
{
	return m_tile.getGlobalBounds();
}

void Tile::setFillColor(const sf::Color color)
{
	m_tile.setFillColor(color);
}

void Tile::edgeTile()
{
	m_edgeTile = true;
}

void Tile::notVisited()
{
	m_visited = false;
	m_distance = 0;
	m_prev = NULL;
}

void Tile::addNeighbor(Tile* tile)
{
	m_neighbors.push_back(tile);
}

void Tile::updatePrevious(Tile* tile)
{
	m_prev = tile;
}

void Tile::setDistance(const int dis)
{
	m_distance = dis;
}

void Tile::setPressed(const bool pressed)
{
	m_pressed = pressed;
	if (pressed)
		setFillColor(sf::Color::Magenta);
	else
		setFillColor(sf::Color::Green);
}

void Tile::setVisited(const bool visited)
{
	m_visited = visited;
}

int Tile::getDistance() const
{
	return m_distance;
}

bool Tile::isPressed() const
{
	return m_pressed;
}

bool Tile::isEdgeTile() const
{
	return m_edgeTile;
}

bool Tile::goodMove() const
{
	return (!m_visited && !m_pressed);
}

bool Tile::able2click(Tile* currTile) const
{
	return (!m_pressed && this != currTile);
}

bool Tile::isContain(const sf::Vector2f& position) const
{
	return m_tile.getGlobalBounds().contains(position);
}

Tile* Tile::getPrevious() const
{
	return m_prev;
}

sf::CircleShape Tile::getTile() const
{
	return m_tile;
}

sf::Vector2f Tile::getPosition() const
{
	return m_tile.getPosition();
}

const std::list<Tile*>& Tile::getNeighborsList() const
{
	return m_neighbors;
}
