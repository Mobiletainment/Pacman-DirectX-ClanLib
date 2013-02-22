/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#include "precomp.h"
#include "DirectionHelper.h"

Direction DirectionHelper::Opposite(Direction direction)
{
	switch (direction)
	{
	case Left:
		return Direction::Right;
		break;
	case Right:
		return Direction::Left;
		break;
	case Top:
		return Direction::Bottom;
		break;
	case Bottom:
		return Direction::Top;
		break;
	default:
		return Direction::None;
		break;
	}
}

CL_Pointf* DirectionHelper::ConvertToVector(Direction direction)
{
	switch(direction)
	{
	case Left:
		return new CL_Pointf(-1,0);
	case Right:
		return new CL_Pointf(1,0);
	case Top:
		return new CL_Pointf(0,-1);
	case Bottom:
		return new CL_Pointf(0,1);
	default:
		return new CL_Pointf(0,0);
	}
}
