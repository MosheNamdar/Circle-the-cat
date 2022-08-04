#pragma once
#include "Macros.h"
#include "Tile.h"
#include <vector>
#include "Resources.h"


class Bfs {
public:
	Bfs();

	void listOfNeibghbors(std::vector<std::vector<Tile*>>& board);
	Tile* minPath(std::vector<std::vector<Tile*>>& board, Tile* position);

private:
	void run(std::vector<std::vector<Tile*>>& board, Tile* tile);
	Tile* minDistanceTile(const std::vector<std::vector<Tile*>>& board) const;
	Tile* nextMove(Tile* minDistanceTile);

};