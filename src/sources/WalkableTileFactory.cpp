/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/
#include "precomp.h"
#include "WalkableTileFactory.h"

WalkableTileFactory::WalkableTileFactory(CL_Sprite* sprite): TileFactory(sprite)
{
}

Tile* WalkableTileFactory::CreateTile(CL_Pointf* position)
{
	Tile* walkableTile= new Tile(_sprite, position);
	walkableTile->Walkable=true;
	return walkableTile;
}