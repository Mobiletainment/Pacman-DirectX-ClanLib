#include "Ghost.h"
#include "Direction.h"
#include <list>
using namespace std;

namespace KI
{
	class Blinky:public Ghost
	{
	protected:
		virtual void CalculatePursuitTarget();
	public:
		Blinky(CL_GraphicContext& gc, Tile* startingTile);
	
		void Update();
	
		~Blinky(void);
	};

}