#include "Ghost.h"
#include "Direction.h"
#include <list>
#include "Tile.h"
#include "Game.h"
using namespace std;

namespace KI
{
	class Inky:public Ghost
	{
	protected:
		CL_Pointf targetPosition;
		Tile virtualTarget;
		virtual void CalculatePursuitTarget();
	public:
		Inky(CL_GraphicContext& gc, Tile* startingTile);
	
		void Update();
	
		~Inky(void);
	};

}