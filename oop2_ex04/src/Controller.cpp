#include "Controller.h"

Controller::Controller()
	:m_level(0), m_window(sf::VideoMode(WIN_W, WIN_H), "Set origin example")
{
}

void Controller::run()
{
	auto board = Board(m_level);
	sf::Vector2f location;

	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::White);
		board.draw(m_window);
		m_window.display();
		levelStatus(board);

		auto event = sf::Event();
		if (board.getAnimation())
		{
			event = sf::Event();
			board.setAnimation(false);
		}

		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseMoved:
				location = (sf::Vector2f)sf::Mouse::getPosition(m_window);
				board.handleClick(location);
				break;

			case sf::Event::MouseButtonReleased:
				location = (sf::Vector2f)sf::Mouse::getPosition(m_window);
				board.press(location, m_window);
				break;
			}
		}

	
	}
}

void Controller::levelStatus(Board& board)
{
	if (Resources::instance().isWonLevel())
	{
		displayMessage(board, "win");
		board.resetScreen(++m_level);
	}
	else if (Resources::instance().isLossLevel())
	{
		displayMessage(board, "loss");
		board.resetScreen(m_level);
	}
}

void Controller::displayMessage(Board& board, const std::string& message)
{
	auto backGround = sf::RectangleShape(sf::Vector2f(800.f, 700.f));
	backGround.setFillColor(sf::Color::White);
	m_window.draw(backGround);
	m_window.display();

	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::White);
		board.drawMessage(message, m_window);
		m_window.display();

		if (auto event = sf::Event{}; m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseButtonReleased:
				return;
			default:
				break;
			}
		}
	}
}
