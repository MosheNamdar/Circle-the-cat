#include "Bfs.h"

Bfs::Bfs()
{
}

void Bfs::listOfNeibghbors(std::vector<std::vector<Tile*>>& board)
{
	int x = 0;
	bool first = true;

	for (int row = 0; row < board.size(); row++)
	{
		row % 2 == 0 ? x = 1 : x = 0;

		for (int col = 0; col < board[row].size(); col++)
		{
			if (row != 0 && col != 0 && row != board.size() - 1 && col != board[10].size() - 1)
			{
				auto currTile = board[row][col];
				if (first)
				{
					auto& resources = Resources::instance();
					resources.setDirection(currTile, board[row - 1][col - x]);
					resources.setDirection(currTile, board[row - 1][col + 1 - x]);
					resources.setDirection(currTile, board[row][col - 1]);
					resources.setDirection(currTile, board[row][col + 1]);
					resources.setDirection(currTile, board[row + 1][col - x]);
					resources.setDirection(currTile, board[row + 1][col + 1 - x]);

					first = false;
				}

				currTile->addNeighbor(board[row - 1][col - x]);
				currTile->addNeighbor(board[row - 1][col + 1 - x]);
				currTile->addNeighbor(board[row][col - 1]);
				currTile->addNeighbor(board[row][col + 1]);
				currTile->addNeighbor(board[row + 1][col - x]);
				currTile->addNeighbor(board[row + 1][col + 1 - x]);
			}
		}
	}
}



Tile* Bfs::minPath(std::vector<std::vector<Tile*>>& board, Tile* position)
{
	run(board, position);
	auto minDistance = minDistanceTile(board);
	return nextMove(minDistance);
}

void Bfs::run(std::vector<std::vector<Tile*>>& board, Tile* tile)
{
	for (auto& row : board)
		for (auto& col : row)
			col->notVisited();

	std::list<Tile*> queue;

	tile->setVisited(true);
	queue.push_back(tile);

	while (!queue.empty())
	{
		auto tile1 = queue.front();
		queue.pop_front();

		for (auto i : tile1->getNeighborsList())
		{
			if (i->goodMove())
			{
				i->setVisited(true);
				i->setDistance(tile1->getDistance() + 1);
				i->updatePrevious(tile1);
				queue.push_back(i);
			}
		}
	}
}

Tile* Bfs::minDistanceTile(const std::vector<std::vector<Tile*>>& board) const
{
	int min = INT_MAX;
	Tile* minDistanceTile = NULL;

	for (auto& row : board)
		for (auto& col : row)
		{
			if (col->isEdgeTile() && col->getPrevious() != NULL)
			{
				if (col->getDistance() < min)
				{
					min = col->getDistance();
					minDistanceTile = col;
				}
			}
		}

	return minDistanceTile;
}

Tile* Bfs::nextMove(Tile* minDistanceTile)
{
	if (minDistanceTile == nullptr)
		return nullptr;

	Tile* nextMove = nullptr;

	while (1)
	{
		if (minDistanceTile->getPrevious()->getPrevious() != NULL)
			minDistanceTile = minDistanceTile->getPrevious();
		else
		{
			nextMove = minDistanceTile;
			break;
		}
	}

	return nextMove;
}
