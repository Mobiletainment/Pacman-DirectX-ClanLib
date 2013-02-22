#include "precomp.h"
#include "Clyde.h"
#include "Game.h"

using namespace KI;

Clyde::Clyde(CL_GraphicContext& gc, Tile* startingTile): Ghost(gc, startingTile)
{
	SetFrames(6, 7);
	patrolTiles[0] = Game::Level->GetTileForPokey();
	patrolTiles[1] = Game::Level->GetTileAtGridPosition(9,26); 
	_targetTile = patrolTiles[1];
	SetCurrentDirection(None);
}

void Clyde::Update()
{
	Ghost::Update();
}

//Pokey has two basic AIs:
//one for when he's far from Pac-Man (beyond 8 grid spaces): Pokey behaves very much like Blinky, trying to move to Pac-Man's exact location
//one for when he is near to Pac-Man: Pokey goes to his home corner in the bottom left of the maze
void Clyde::CalculatePursuitTarget()
{
	//calculate how many grid spaces Clyde is away from Pacman
	CL_Pointf pacmanPos = *Game::Pacman->CurrentTile()->Position;
	CL_Pointf distance = *this->_currentTile->Position - pacmanPos;

	if (distance.x < 0) //we're only interested in the distance
		distance.x *= -1;
	if (distance.y < 0)
		distance.y *= -1;

	int gridSpacesAhead = (int)(distance.x / Tile::TileSize); //how many grid spaces in horizontal direction
	gridSpacesAhead += (int) (distance.y / Tile::TileSize); //add grid spaces in vertical direction

	if (gridSpacesAhead > 8) //beyond 8 grid spaces away from Pokey: behaves like Blinky, trying to move to Pac-Man's exact location
		_targetTile = Game::Pacman->CurrentTile();
	else //go to the home corner
	{
		if (_targetTile != patrolTiles[0] && _targetTile != patrolTiles[1])
			_targetTile = patrolTiles[0];

		else if (_currentTile == _targetTile) //if ghost has reached the target tile, toggle next one
		{
			if (_targetTile == patrolTiles[0])
				_targetTile = patrolTiles[1];
			else
				_targetTile = patrolTiles[0];
		}
	}
}



Clyde::~Clyde(void)
{
}
