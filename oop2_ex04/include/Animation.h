#pragma once
#include "Macros.h"
#include "Resources.h"


class Animation {
public:
	Animation();

	void move(const sf::Vector2f& direction);
	void reset();
	void setSprite(sf::Sprite& sprite);

private:
	void UpdateTopSide(Top, Way way = Way::Regular);
	void UpdateLeftSide();

	sf::IntRect m_intRect;
	sf::Sprite* m_sprite = nullptr;
};