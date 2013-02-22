#include "precomp.h"
#include "Ghost.h"
#include "DirectionHelper.h"
#include "math.h"

using namespace KI;

Ghost::Ghost(CL_GraphicContext& gc, Tile* startingTile):Character(gc, startingTile, "resources/sprites/monster.png")
{
	patrolTiles = vector<Tile *>(2);
	_gameMode = GameMode::Patrol;
	_lockDirection = false;
}

void Ghost::Update()
{
	//only do target calculation once every tile
	//if direction is locked, don't recalculate the movement
	if (fmod(Position->x, Tile::TileSize) == 0 && fmod(Position->y, Tile::TileSize) == 0 && _lockDirection == false)
	{
		if (_gameMode == GameMode::Patrol) //Patrol behavior is the same for all ghosts																	
		{
			//if ghost has reached the patrol-checkpoint, toggle next one
			if (_currentTile == _targetTile) //checkpoint reached
			{
				if (_targetTile == patrolTiles[0])
					_targetTile = patrolTiles[1];
				else
					_targetTile = patrolTiles[0];
			}
		}
		else if (_gameMode == GameMode::Pursuit) //Pursuit behavior needs to be implemented for each ghost differently
		{
			CalculatePursuitTarget(); //call abstract method
		}
		else //Frigtened Mode
		{
			//randomize movement
			int direction;

 			while(1)
			{
				direction = (std::rand() % 4) + 1;

				if (_currentTile->GetNeighbor((Direction)direction) == NULL)
				{
					//target tile does not exist, try with new direction
					continue;
				}
				else if (_nextDirection == direction)
				{
					continue;
				}

				if (direction == Left && _currentDirection != Right)
				{
					break;
				}
				else if (direction == Right && _currentDirection != Left)
				{
					break;
				}
				else if (direction == Top && _currentDirection != Bottom)
				{
					break;
				}
				else if (direction == Bottom && _currentDirection != Top)
				{
					break;
				}
			}
			
			_targetTile = _currentTile->GetNeighbor((Direction)direction);
			
		}

		CL_Pointf *targetPosition = _targetTile->Position;

		float deltaX = targetPosition->x - Position->x;
		float deltaY = targetPosition->y - Position->y;

		float distanceX = deltaX * deltaX;
		float distanceY = deltaY * deltaY;

		//if Ghost made a decision on how to move to the target and gets to a point where the distances in both
		//directions are equal, there's a 50% chance that it reverts its decision and handles the movement to the
		//target the opposite way. To avoid this, weight the current Direction a bit more to maintain the direction
		if (distanceX == distanceY && CurrentDirection() != None)
		{
			if (CurrentDirection() == Left || CurrentDirection() == Right)
				distanceX += 1.0f;
			else
				distanceY += 1.0f;
		}

		if (distanceX > distanceY) //move right or left first
		{
			if (deltaX < 0) //Move left if possible
				SetCurrentDirection(Left);
			else if (deltaX >= 0) //Move right if possible
				SetCurrentDirection(Right);

			if (deltaY < 0) //Backup case if movement not possible
			{
				_nextDirection = Top;
			}
			else if (deltaY >= 0)
			{
				_nextDirection = Bottom;
			}
		}
		else //move up or down first
		{
			if (deltaY < 0)
				SetCurrentDirection(Top);
			else if (deltaY >= 0)
				SetCurrentDirection(Bottom);

			if (deltaX < 0)  //Backup case if movement not possibl
				_nextDirection = Left;
			else if (deltaX >= 0)
				_nextDirection = Right;
		}
	}

	//Move to shortest direction first, if not possible then take the other direction
	if (_currentTile->GetNeighbor(CurrentDirection())->Walkable)
	{
		_lockDirection = false; //unlock in case direction was locked, because now we finally got the movement into the direction we wanted at first place
		this->MoveInDirection(CurrentDirection());
	}
	else if (_currentTile->GetNeighbor(_nextDirection)->Walkable)
	{
		_lockDirection = true;
		this->MoveInDirection(_nextDirection);
	}
	//if movement in both target directions are not possbile, try the other ways
	//Begin with direction the ghost is not corrently moving at (nextDirection) to avoid zig-zag 
	//begin with moving the opposite way of the longer direction
	else if (_currentTile->GetNeighbor(DirectionHelper::Opposite(_nextDirection))->Walkable && _lockDirection == false) //only if direction is not locked, otherwise we get a zig zag deadlock
	{
		_lockDirection = true;
		_nextDirection = DirectionHelper::Opposite(_nextDirection);
		//_nextDirection = temp;
		this->MoveInDirection(_nextDirection);
	}
	else if (_currentTile->GetNeighbor(DirectionHelper::Opposite(CurrentDirection()))->Walkable)
	{
		_currentDirection = DirectionHelper::Opposite(CurrentDirection());
		this->MoveInDirection(_currentDirection);
	}

	if (_currentTile->Position->x - Position->x <= -Tile::TileSize)
	{
		_currentTile = _currentTile->GetNeighbor(Right);

		if (Position->x > 675.0f) //in case ghost walked through right exit
			Position->x = 0.0f; //arriving on left end
	}
	else if (_currentTile->Position->x - Position->x >= Tile::TileSize)
	{
		_currentTile = _currentTile->GetNeighbor(Left);

		if (Position->x < 0.0f) //in case ghost walked through left exit
			Position->x = _currentTile->Position->x; //arriving on right end
	}
	else if (_currentTile->Position->y - Position->y >= Tile::TileSize)
		_currentTile = _currentTile->GetNeighbor(Top);
	else if (_currentTile->Position->y - Position->y <= -Tile::TileSize)
		_currentTile = _currentTile->GetNeighbor(Bottom);
	

}

void Ghost::SetCurrentDirection(Direction direction)
{
	_currentDirection = direction; //finally, set the direction the character is looking now
}

void Ghost::NotifyGameModeChanged(GameMode mode)
{
	_gameMode = mode;

	if (mode == Patrol)
	{
		_targetTile = patrolTiles[0];
		this->_sprite->set_alpha(1.0);
	}
	else if (mode == Pursuit)
	{
		this->_sprite->set_alpha(1.0f);
	}
	else if (mode == Frightened)
	{
		this->_sprite->set_alpha(0.5);
	}
}


Ghost::~Ghost(void)
{
}
