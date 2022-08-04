#include "Cat.h"

Cat::Cat()
	:m_sprite(Resources::instance().getTexture())
{
	m_sprite.setOrigin({ 56, 56 });
	m_animation.setSprite(m_sprite);
}

void Cat::initBfs(std::vector<std::vector<Tile*>>& board)
{
	m_bfs.listOfNeibghbors(board);
}

void Cat::nextMove(std::vector<std::vector<Tile*>>& board)
{
	if (m_tilePosition->isEdgeTile())
	{
		Resources::instance().setLossLevel();
		return;
	}

	Tile* next = NULL;
	if (!m_catCaught)
		next = m_bfs.minPath(board, m_tilePosition);
	if (!next)
		m_catCaught = true; //:)

	if (m_catCaught)
	{
		next = move2AnyDirection();
		if (!next)
		{
			Resources::instance().setWonLevel();
			return;
		}
	}
	m_tilePosition = next;
}

void Cat::move(const sf::Vector2f& direction)
{
	m_sprite.move(direction);
	m_animation.move(direction);
}

void Cat::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void Cat::setPhysicalPosition(Tile* tile)
{
	m_tilePosition = tile;
	m_sprite.setPosition(m_tilePosition->getPosition());
}

void Cat::reset(Tile* tile)
{
	m_catCaught = false;
	m_tilePosition = tile;
	m_sprite.setPosition(tile->getPosition());
	m_animation.reset();
}

const sf::Sprite& Cat::getSprite() const
{
	return m_sprite;
}

Tile* Cat::move2AnyDirection() const
{
	auto& optionalMoves = m_tilePosition->getNeighborsList();
	int counter = 0;

	for (auto tile : optionalMoves)
		if (!tile->isPressed())
			counter++;

	if (!counter)
		return nullptr;
	auto num = 1 + rand() % ((counter + 1) - 1);
	counter = 0;

	for (auto tile : optionalMoves)
		if (!tile->isPressed())
		{
			if (++counter == num)
				return tile;
		}
	return nullptr;
}

Tile* Cat::getPosition() const
{
	return m_tilePosition;
}
