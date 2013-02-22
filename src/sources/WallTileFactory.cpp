/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#include "precomp.h"
#include "WallTileFactory.h"

WallTileFactory::WallTileFactory(CL_Sprite* sprite): TileFactory(sprite)
{
}

Tile* WallTileFactory::CreateTile(CL_Pointf* position)
{
	Tile* wallTile= new Tile(_sprite, position);
	return wallTile;
}
