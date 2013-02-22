/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/
#include "precomp.h"
#include "Tile.h"

float Tile::TileSize=25.0f;

Tile::Tile()
{
	_left = NULL;
	_right = NULL;
	_top = NULL;
	_bottom = NULL;

	Size=new CL_Sizef(TileSize, TileSize);
}

Tile::Tile(CL_Sprite* sprite, CL_Pointf* position)
{
	Walkable=false;
	Eatable=false;
	IsPill=false;
	_left = NULL;
	_right = NULL;
	_top = NULL;
	_bottom = NULL;


	_sprite=sprite;
	Position=new CL_Pointf(position->x*TileSize, position->y*TileSize);
	Size=new CL_Sizef(TileSize, TileSize);
}

void Tile::Eat()
{
	_sprite=NULL;
	Eatable=false;
}

Tile* Tile::GetNeighbor(Direction direction)
{
	switch (direction)
	{
		case Direction::Left:
			return _left;
		case Direction::Top:
			return _top;
		case Direction::Right:
			return _right;
		case Direction::Bottom:
			return _bottom;
		default:
			return this;
	}
}

void Tile::SetLeft(Tile* left)
{
	_left=left;
	_left->_right=this;
}

void Tile::SetTop(Tile* top)
{
	_top=top;
	_top->_bottom=this;
}

void Tile::SetRight(Tile* right)
{
	_right=right;
	_right->_left=this;
}

void Tile::SetBottom(Tile* bottom)
{
	_bottom=bottom;
	_bottom->_top=this;
}

void Tile::Render(CL_GraphicContext* gc)
{
	if(_sprite!=NULL)
	{
		_sprite->draw(*gc,CL_Rectf(0,0,100,100),CL_Rectf(Position->x, Position->y, Position->x+Size->width,Position->y+Size->height));
	}
}

Tile::~Tile(void)
{
	_left=NULL;
	_top=NULL;
	_right=NULL;
	_bottom=NULL;
}
