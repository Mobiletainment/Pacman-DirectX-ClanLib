/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/
#include "precomp.h"
#include "TileFactory.h"

TileFactory::TileFactory(CL_Sprite* sprite)
{
	_sprite=sprite;
}

TileFactory::~TileFactory()
{
	_sprite=NULL;
}
