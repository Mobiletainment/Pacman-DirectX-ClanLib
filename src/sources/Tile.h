/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include "Direction.h"

class Tile
{
protected:
	Tile* _left;
	Tile* _top;
	Tile* _right;
	Tile* _bottom;

	CL_Sprite* _sprite;


public:
	static float TileSize;
	CL_Pointf* Position;
	CL_Sizef* Size;
	bool Walkable;
	bool Eatable;
	bool IsPill;

	void Eat();

	Tile* GetNeighbor(Direction direction);

	void SetLeft(Tile* left);
	void SetTop(Tile* top);
	void SetRight(Tile* right);
	void SetBottom(Tile* bottom);

	void Render(CL_GraphicContext* gc);

	Tile(CL_Sprite* sprite, CL_Pointf* position);
	Tile();
	~Tile(void);
};

