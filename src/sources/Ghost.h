
#pragma once
#include "Character.h"
#include "Direction.h"
#include <vector>
#include "GameMode.h"
using namespace std;

namespace KI
{
	class Ghost:public Character
	{	
		private:
			GameMode _gameMode;
			bool _lockDirection;
		protected:
			vector<Tile *> patrolTiles;
			virtual void SetCurrentDirection(Direction direction);
			
		public:
			Ghost(CL_GraphicContext& gc, Tile* startingTile);
			virtual void Update();	
			virtual void CalculatePursuitTarget() = 0;
			void NotifyGameModeChanged(GameMode mode);
			~Ghost(void);
	};

}