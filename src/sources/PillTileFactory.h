/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include "EatableTileFactory.h"
class PillTileFactory : public EatableTileFactory
{
public:
	PillTileFactory(CL_Sprite* sprite);
	~PillTileFactory();
	Tile* CreateTile(CL_Pointf* position);
};

