#include "Board.h"

Board::Board(const int level)
	:m_steps(0), m_level(level +1), m_animation(false)
{
	Resources::instance().restartLevel();
	initBoard();
	initLevel(Level(level));
	initMessage();
	m_cat.setPhysicalPosition(m_tiles[5][5]);
	m_cat.initBfs(m_tiles);
	
}

Board::~Board()
{
	for (auto& row : m_tiles)
		for (auto col : row)
			delete col;
}

void Board::draw(sf::RenderWindow& window)
{
	for (int r = 0; r < 11; r++)
		for(int c = 0; c < 11; c++)
			m_tiles[r][c]->draw(window);

	window.draw(m_cat.getSprite());
	window.draw(m_message["steps"]);
	window.draw(m_message["level"]);
}

void Board::initBoard()
{
	float x;

	for (int row = 0; row < 11; row++)
	{
		auto temp = std::vector<Tile*>();
		for (int col = 0; col < 11; col++)
		{
			if (row % 2 == 0)
				x = float(col + 0.6);
			else
				x = float(col + 1.1);

			auto location = sf::Vector2f(float(x * 65), float((row+1) * 55));
			auto tile = new Tile(location);
			if (row == 0 || col == 0 || row == 10 || col == 10)
				tile->edgeTile();

			temp.push_back(tile);
		}
		m_tiles.push_back(temp);
	}
}

void Board::updateCat(sf::RenderWindow& window)
{
	m_animation = true;
	auto path = findPath();

	for (auto i = 0; i < 45; i++)
	{
		window.clear(sf::Color::White);
		if (i % 5 == 0)
			m_cat.move(path);

		draw(window);
		window.display();
	}
}

void Board::initLevel(Level level)
{
	if (level == Level::Easy)
		markTiles(EASY);
	else if (level == Level::Medium)
		markTiles(MEDIUM);
	else if (level == Level::Hard)
		markTiles(HARD);
	else
		markTiles(HARD);
}

void Board::markTiles(const int difficulty)
{
	int x = 0;
	int y = 0;
	bool catPlace = true;
	for (int i = 0; i < difficulty; i++)
	{
		while (catPlace)
		{
			x = rand() % 11;
			y = rand() % 11;
			if (x != 5 || y != 5)
				catPlace = false;
		}
		m_tiles[x][y]->setPressed(true);
		catPlace = true;
	}
}

void Board::initMessage()
{
	std::string steps = std::to_string(m_steps);
	std::string levels = std::to_string(m_level);

	auto& font = Resources::instance().getFont();
	sf::Text win;
	win.setFont(font);
	win.setString("Congratulations, you circled the cat!");
	win.setCharacterSize(35);
	win.setFillColor(sf::Color::Magenta);
	win.setPosition(150, 350);

	sf::Text loss;
	loss.setFont(font);
	loss.setString("Oops! the cat run away, try again!");
	loss.setCharacterSize(35);
	loss.setFillColor(sf::Color::Magenta);
	loss.setPosition(150, 350);

	sf::Text continuem;
	continuem.setFont(font);
	continuem.setString("Please press to continue");
	continuem.setCharacterSize(25);
	continuem.setFillColor(sf::Color::Magenta);
	continuem.setPosition(280, 400);

	sf::Text step;
	step.setFont(font);
	step.setString("steps: " + steps);
	step.setCharacterSize(35);
	step.setFillColor(sf::Color::Magenta);
	step.setPosition(200, 710);

	sf::Text level;
	level.setFont(font);
	level.setString("level: " + levels);
	level.setCharacterSize(35);
	level.setFillColor(sf::Color::Magenta);
	level.setPosition(500, 710);

	m_message["win"] = win;
	m_message["loss"] = loss;
	m_message["continue"] = continuem;
	m_message["steps"] = step;
	m_message["level"] = level;
}

sf::Vector2f Board::findPath()
{
	auto source = m_cat.getPosition();
	m_cat.nextMove(m_tiles);
	auto destination = m_cat.getPosition();
	auto direction = Resources::instance().getDirection(source, destination);

	if (!direction && m_cat.getPosition()->isEdgeTile())
	{
		auto& directions = Resources::instance().getDirections();

		if (m_cat.getSprite().getPosition().x < 100)
			return directions[Left];
		if (m_cat.getSprite().getPosition().x > 700)
			return directions[Right];
		if (m_cat.getSprite().getPosition().y < 100)
			return directions[Top_Left];
		if (m_cat.getSprite().getPosition().y > 600)
			return directions[Bottom_Left];
	}
	return direction;
}

void Board::handleClick(sf::Vector2f& location)
{
	for (int r = 0; r < 11; r++)
		for (int c = 0; c < 11; c++)
		{
			if (m_tiles[r][c]->getGlobalBounds().contains(location))
			{
				if (m_tiles[r][c]->able2click(m_cat.getPosition()))
					m_tiles[r][c]->setFillColor(sf::Color::Magenta);
			}
			else
			{
				if(!m_tiles[r][c]->isPressed())
					m_tiles[r][c]->setFillColor(sf::Color::Green);
			}
		}		
}

void Board::press(const sf::Vector2f& location, sf::RenderWindow& window)
{
	if (m_animation)
		return;
	for (auto& row : m_tiles)
		for (auto& tile : row)
			if (tile->isContain(location))
			{
				if (tile->able2click(m_cat.getPosition()))
				{
					tile->setPressed(true);
					m_steps++;
					m_message["steps"].setString("steps: " + std::to_string(m_steps));
					updateCat(window);
				}
				return;
			}
}

void Board::drawMessage(const std::string& message, sf::RenderWindow& window)
{
	window.draw(m_message[message]);
	window.draw(m_message["continue"]);
	window.draw(m_message["steps"]);
	window.draw(m_message["level"]);
}

void Board::resetScreen(const int level)
{
	Resources::instance().restartLevel();

	for (auto& row : m_tiles)
		for (auto col : row)
			col->setPressed(false);

	initLevel(Level(level));
	m_steps = 0;
	m_level = level + 1;
	m_message["steps"].setString("steps: " + std::to_string(m_steps));
	m_message["level"].setString("level: " + std::to_string(m_level));
	m_cat.reset(m_tiles[5][5]);
}

bool Board::getAnimation() const
{
	return m_animation;
}

void Board::setAnimation(const bool status)
{
	m_animation = status;
}
