#pragma once
#include "Macros.h"
#include <list>


class Tile 
{
public:
	Tile(const sf::Vector2f& position);

	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBounds();
	void setFillColor(const sf::Color color);
	void edgeTile();
	void notVisited();
	void addNeighbor(Tile* tile);
	void updatePrevious(Tile* tile);
	void setDistance(const int dis);
	void setPressed(const bool pressed);
	void setVisited(const bool visited);
	int getDistance() const;
	bool isPressed() const;
	bool isEdgeTile() const;
	bool goodMove() const;
	bool able2click(Tile* currTile) const;
	bool isContain(const sf::Vector2f&) const;
	Tile* getPrevious() const;
	sf::CircleShape getTile() const;
	sf::Vector2f getPosition() const;
	const std::list<Tile*>& getNeighborsList() const;

private:
	sf::CircleShape m_tile;
	bool m_pressed = false;
	bool m_visited = false;
	bool m_edgeTile = false;
	Tile* m_prev = NULL;
	int m_distance = 0;
	std::list<Tile*> m_neighbors;
};