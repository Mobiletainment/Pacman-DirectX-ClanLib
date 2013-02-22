/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/
#include "precomp.h"
#include "PillTileFactory.h"

PillTileFactory::PillTileFactory(CL_Sprite* sprite): EatableTileFactory(sprite)
{
}

Tile* PillTileFactory::CreateTile(CL_Pointf* position)
{
	Tile* eatableTile= EatableTileFactory::CreateTile(position);
	eatableTile->IsPill=true;
	return eatableTile;
}

