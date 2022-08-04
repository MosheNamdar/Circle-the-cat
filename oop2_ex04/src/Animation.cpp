#include "Animation.h"

Animation::Animation()
	:m_intRect({0, 10, 112, 112})
{
}

void Animation::move(const sf::Vector2f& direction)
{
	auto& directions = Resources::instance().getDirections();

	if (directions[Top_Left] == direction)
		UpdateTopSide(Top::Last, Way::Reverse);

	else if (directions[Top_Right] == direction)
		UpdateTopSide(Top::Last);

	else if (directions[Left] == direction)
		UpdateTopSide(Top::Middle, Way::Reverse);

	else if (directions[Right] == direction)
		UpdateTopSide(Top::Middle);

	else if (directions[Bottom_Left] == direction)
		UpdateTopSide(Top::First, Way::Reverse);

	else if (directions[Bottom_Right] == direction)
		UpdateTopSide(Top::First);

	else
		return;

	UpdateLeftSide();
	m_sprite->setTextureRect(m_intRect);
}

void Animation::reset()
{
	m_intRect = { 0, 10, 112, 112 };
	m_sprite->setScale(1, 1);
	m_sprite->setTextureRect(m_intRect);
}

void Animation::setSprite(sf::Sprite& sprite)
{
	m_sprite = &sprite;
	m_sprite->setTextureRect(m_intRect);
}

void Animation::UpdateTopSide(Top top, Way way)
{
	m_intRect.top = int(top);
	m_sprite->setScale(float(way), 1.f);
}

void Animation::UpdateLeftSide()
{
	m_intRect.left = (m_intRect.left + m_intRect.width) % (m_intRect.width * 9);	
}
