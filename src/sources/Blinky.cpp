#include "precomp.h"
#include "Blinky.h"
#include "Game.h"

using namespace KI;

Blinky::Blinky(CL_GraphicContext& gc, Tile* startingTile): Ghost(gc, startingTile)
{
	SetFrames(0, 1);
	patrolTiles[0] = Game::Level->GetTileForBlinky();
	patrolTiles[1] = Game::Level->GetTileAtGridPosition(21,5); 
	_targetTile = patrolTiles[1];
	SetCurrentDirection(None);
}

void Blinky::Update()
{
	Ghost::Update();
}

void Blinky::CalculatePursuitTarget()  //Shadow tries to find the quickest route to Pac-Man's exact position.
{
	_targetTile = Game::Pacman->CurrentTile();
}



Blinky::~Blinky(void)
{
}
