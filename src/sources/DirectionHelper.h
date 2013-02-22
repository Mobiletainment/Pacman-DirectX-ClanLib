/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include "Direction.h"

class DirectionHelper
{
public:
	static Direction Opposite(Direction direction);
	static CL_Pointf* ConvertToVector(Direction direction);
};

