/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include "Tile.h"
class TileFactory
{
protected:
	CL_Sprite* _sprite;
	TileFactory(CL_Sprite* sprite);
	~TileFactory();
public:
	virtual Tile* CreateTile(CL_Pointf* position){return NULL;};
};

