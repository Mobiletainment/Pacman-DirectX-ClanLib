#include "precomp.h"
#include "Character.h"

using namespace KI;

const float Character::_frameSize=32.0f;

Character::Character(CL_GraphicContext& gc, Tile* startingTile, string spritePath)
{
	_gc=gc;
	_currentTile=startingTile;
	_walkSpeed = 2.5f;
	_currentDirection = Right;
	_nextDirection = None;
	Position=new CL_Pointf(_currentTile->Position->x, _currentTile->Position->y);
	
	_sprite=SpriteManager::LoadSprite(_gc, spritePath);

	_startFrame=0;
	_endFrame=0;
	_currentFrame=0;
	_elapsedFrames=0;
}

void Character::SetFrame(int frame)
{
	SetFrames(frame, frame);
}

void Character::SetFrames(int startFrame, int endFrame)
{
	_startFrame=startFrame;
	_endFrame=endFrame;
	_currentFrame=_startFrame;
}

void Character::Update()
{
	CheckAnimation();
	cout << Position->x << ", " << Position->y;
	if (_nextDirection != None && _currentTile->GetNeighbor(_nextDirection)->Walkable) //do movement in next direction if possible
	{
		_targetTile = _currentTile->GetNeighbor(_nextDirection);
		SetCurrentDirection(_nextDirection);
	}
	else if (_currentTile->GetNeighbor(_currentDirection)->Walkable)
	{
		_targetTile = _currentTile->GetNeighbor(_currentDirection);
	}
}

void Character::SetCurrentDirection(Direction direction)
{
	//First, inverse rotation of current Direction, so that Pacman is looking to right direction again
	switch (_currentDirection)
	{
	case Left:
		this->_sprite->rotate(CL_Angle::from_degrees(-180.0f));
		break;
	case Right:
		//this->_sprite->rotate(CL_Angle::from_degrees(0.0f));
		break;
	case Top:
		this->_sprite->rotate(CL_Angle::from_degrees(-270.0f));
		break;
	case Bottom:
		this->_sprite->rotate(CL_Angle::from_degrees(-90.0f));
		break;
	}

	//From here, rotate the sprite (source = right direction) so it's looking in the correct direction
	switch (direction)
	{
	case Left:
		this->_sprite->rotate(CL_Angle::from_degrees(180.0f));
		break;
	case Right:
		//this->_sprite->rotate(CL_Angle::from_degrees(0.0f));
		break;
	case Top:
		this->_sprite->rotate(CL_Angle::from_degrees(270.0f));
		break;
	case Bottom:
		this->_sprite->rotate(CL_Angle::from_degrees(90.0f));
		break;
	}

	_currentDirection = direction; //finally, set the direction the character is looking now
	_nextDirection = None;
}

Direction Character::CurrentDirection()
{
	return _currentDirection;
}

Tile* Character::CurrentTile() const
{
	return _currentTile;
}

void Character::MoveInDirection(const Direction &direction)
{
	switch (direction)
	{
	case Left:
		Position->x -= _walkSpeed;
		break;
	case Right:
		Position->x += _walkSpeed;
		break;
	case Top:
		Position->y -= _walkSpeed;
		break;
	case Bottom:
		Position->y += _walkSpeed;
		break;
	}
}

void Character::CheckAnimation()
{
	_elapsedFrames++;

	if(_elapsedFrames>=10)
	{
		_elapsedFrames=0;
		_currentFrame++;

		if(_currentFrame>_endFrame)
			_currentFrame=_startFrame;
	}
}

void Character::Render()
{
	_sprite->draw(_gc,CL_Rectf(_currentFrame*_frameSize,0,_currentFrame*_frameSize+_frameSize,_frameSize),CL_Rectf(Position->x, Position->y, Position->x  + 30, Position->y+ 30));
}

void Character::Move(Direction direction)
{
	_nextDirection = direction;
	
}

Character::~Character(void)
{
}
