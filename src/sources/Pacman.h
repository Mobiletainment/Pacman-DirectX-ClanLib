#pragma once
#include "Character.h"
#include "Direction.h"
#include <list>
using namespace std;

namespace KI
{
	class Pacman:public Character
	{
	public:
		Pacman(CL_GraphicContext& gc, Tile* startingTile);
	
		void Update();
		~Pacman(void);
	};
}
