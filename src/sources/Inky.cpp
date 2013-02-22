#include "precomp.h"
#include "Inky.h"


using namespace KI;

Inky::Inky(CL_GraphicContext& gc, Tile* startingTile): Ghost(gc, startingTile)
{
	SetFrames(4, 5);
	patrolTiles[0] = Game::Level->GetTileForBashful();
	patrolTiles[1] = Game::Level->GetTileAtGridPosition(18,26); 
	_targetTile = patrolTiles[1];
	SetCurrentDirection(None);
}

void Inky::Update()
{
	Ghost::Update();
}

//Bashful draws a line from Shadow to the spot two squares in front of Pac-Man, and extends that line twice as far
void Inky::CalculatePursuitTarget()
{
	Direction direction = Game::Pacman->CurrentDirection();

	CL_Pointf pacmanPos = *Game::Pacman->CurrentTile()->Position;
	float pointAhead = Tile::TileSize * 2;
	switch (direction)
	{
	case Left:
		pacmanPos.x -= pointAhead;
		break;
	case Right:
		pacmanPos.x += pointAhead;
		break;
	case Top:
		pacmanPos.y -= pointAhead;
		break;
	case Bottom:
		pacmanPos.y += pointAhead;
		break;
	}

	CL_Pointf blinkyPos = *Game::Blinky->CurrentTile()->Position;

	targetPosition = pacmanPos - blinkyPos; //length of direction
	targetPosition *= 2; //twice of length
	targetPosition += blinkyPos;
	virtualTarget.Position = &targetPosition;
	_targetTile = &virtualTarget;
}



Inky::~Inky(void)
{
}
