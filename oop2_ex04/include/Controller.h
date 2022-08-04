#pragma once
#include "Macros.h"
#include "Board.h"

class Controller {
public:
	Controller();

	void run();
	void levelStatus(Board& board);
	void displayMessage(Board& board, const std::string& message);

private:
	sf::RenderWindow m_window;
	int m_level;
};