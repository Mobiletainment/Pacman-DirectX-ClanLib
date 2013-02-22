#include "Ghost.h"
#include "Direction.h"
#include <list>
#include "Tile.h"
using namespace std;

namespace KI
{
	class Pinky:public Ghost
	{
	protected:
		CL_Pointf targetPosition;
		Tile virtualTarget;
		virtual void CalculatePursuitTarget();
	public:
		Pinky(CL_GraphicContext& gc, Tile* startingTile);
	
		void Update();
	
		~Pinky(void);
	};

}