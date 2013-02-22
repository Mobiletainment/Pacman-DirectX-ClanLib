#include "precomp.h"
#include "Pacman.h"

using namespace KI;

Pacman::Pacman(CL_GraphicContext& gc, Tile* startingTile):Character(gc, startingTile, "resources/sprites/pacman.png")
{
	SetFrames(3,4);
}

void Pacman::Update()
{
	Character::Update();

	if (_targetTile != _currentTile)
	{
		CL_Pointf *targetPosition = _targetTile->Position;

		if (targetPosition->x < Position->x && CurrentDirection() == Right && Position->x >= 675.0f) //Special Case: Walking through Right tunnel exiting from left side
		{
			Position->x += _walkSpeed;

			if (Position->x >= 675.0f)
			{
				Position->x = -5.0f;
			}
		}
		else if (targetPosition->x < Position->x) //Walk left
		{
			Position->x -= _walkSpeed;
		}
		else if (targetPosition->x > Position->x && CurrentDirection() == Left && Position->x <= 5.0f) //Special Case: Walking through left tunnel exiting in same direction from right side
		{
			Position->x -= _walkSpeed;

			if (Position->x <= 0.0f)
			{
				Position->x += targetPosition->x;
			}
		}
		else if (targetPosition->x > Position->x) //Walk Right
		{
			Position->x += _walkSpeed;
		}
		else if (targetPosition->y < Position->y) //Walk Up
		{
			Position->y -= _walkSpeed;
		}
		else if (targetPosition->y > Position->y) //Walk Down
		{
			Position->y += _walkSpeed;
		}

		if (targetPosition->x == Position->x && targetPosition->y == Position->y)
		{
			_currentTile = _targetTile;
		}
	}
}

Pacman::~Pacman(void)
{
}
