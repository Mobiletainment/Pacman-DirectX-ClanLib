/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include "WalkableTileFactory.h"
class EatableTileFactory : public WalkableTileFactory
{
public:
	EatableTileFactory(CL_Sprite* sprite);
	Tile* CreateTile(CL_Pointf* position);
};

