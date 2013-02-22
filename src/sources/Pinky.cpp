#include "precomp.h"
#include "Pinky.h"
#include "Game.h"

using namespace KI;

Pinky::Pinky(CL_GraphicContext& gc, Tile* startingTile): Ghost(gc, startingTile)
{
	SetFrames(2, 3);
	patrolTiles[0] = Game::Level->GetTileForSpeedy();
	patrolTiles[1] = Game::Level->GetTileAtGridPosition(6,5); 
	_targetTile = patrolTiles[1];
	SetCurrentDirection(None);
}

void Pinky::Update()
{
	Ghost::Update();
}

void Pinky::CalculatePursuitTarget() //the place that is four grid spaces ahead of Pacman in the direction that Pac-Man is facing.
{
	Direction direction = Game::Pacman->CurrentDirection(); //Get the direction Pacman is looking

	/*
	////Alternatively, instead of Virtual Targets, we could navigate to real targets, but we have to check if the target is out of bounds 
		_targetTile = Game::Pacman->CurrentTile();
	for (int i = 0; i < 4; ++i) //avoid position that do not exist
	{
		Tile *nextTile = _targetTile->GetNeighbor(direction);
		
		if (nextTile == NULL || nextTile == Game::Level->GetTileForExitLeft() || nextTile == Game::Level->GetTileForExitRight())
			break;
		_targetTile = nextTile;
	}
	*/

	//2nd Method:
	CL_Pointf pacmanPos = *Game::Pacman->CurrentTile()->Position;
	float pointAhead = Tile::TileSize * 4; //length of 4 Tiles
	switch (direction)
	{
	case Left:
		pacmanPos.x -= pointAhead; //4 Grid spaces left of pacman
		break;
	case Right:
		pacmanPos.x += pointAhead; //4 Grid spaces right of pacman
		break;
	case Top:
		pacmanPos.y -= pointAhead; //4 Grid spaces above pacman
		break;
	case Bottom:
		pacmanPos.y += pointAhead; //4 Grid spaces below pacman
		break;
	}

	//create a "Virtual" Target Object for the position that Pinky should move to
	targetPosition = pacmanPos;
	virtualTarget.Position = &targetPosition;
	_targetTile = &virtualTarget;
}



Pinky::~Pinky(void)
{
}
