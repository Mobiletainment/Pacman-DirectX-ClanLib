/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#include "precomp.h"
#include "EatableTileFactory.h"

EatableTileFactory::EatableTileFactory(CL_Sprite* sprite): WalkableTileFactory(sprite)
{
}

Tile* EatableTileFactory::CreateTile(CL_Pointf* position)
{
	Tile* eatableTile= WalkableTileFactory::CreateTile(position);
	eatableTile->Eatable=true;
	return eatableTile;
}

