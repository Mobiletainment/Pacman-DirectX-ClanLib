/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include "TileFactory.h"
class WallTileFactory: public TileFactory
{
public:
	WallTileFactory(CL_Sprite* sprite);
	Tile* CreateTile(CL_Pointf* position);
};