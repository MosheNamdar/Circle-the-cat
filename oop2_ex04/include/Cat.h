#pragma once
#include "Macros.h"
#include "Bfs.h"
#include "Tile.h"
#include "Resources.h"
#include "animation.h"
#include <list>


class Cat {
public:
	Cat();

	void initBfs(std::vector<std::vector<Tile*>>& board);
	void nextMove(std::vector<std::vector<Tile*>>& board);
	void move(const sf::Vector2f&);
	void setPosition(const sf::Vector2f& position);
	void setPhysicalPosition(Tile* tile);
	void reset(Tile* tile);
	const sf::Sprite& getSprite() const;
	Tile* move2AnyDirection() const;
	Tile* getPosition() const;

private:
	sf::Sprite m_sprite;
	Bfs m_bfs;
	Animation m_animation;
	Tile* m_tilePosition = NULL;
	bool m_catCaught = false;

};