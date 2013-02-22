#include "Ghost.h"
#include "Direction.h"
#include <list>
using namespace std;

namespace KI
{
	class Clyde:public Ghost
	{
	protected:
		virtual void CalculatePursuitTarget();
	public:
		Clyde(CL_GraphicContext& gc, Tile* startingTile);
	
		void Update();
	
		~Clyde(void);
	};

}