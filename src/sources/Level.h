#pragma once
#include <strstream>

#include <map>
#include "SpriteManager.h"
#include "TileFactory.h"
#include "WallTileFactory.h"
#include "WalkableTileFactory.h"
#include "EatableTileFactory.h"
#include "PillTileFactory.h"
#include "Tile.h"
#include <vector>

using namespace std;

namespace KI
	{
	class Level
	{
	private:
			CL_GraphicContext _gc;
	public:
		unsigned int SizeX;
		unsigned int SizeY;
		Level(CL_GraphicContext gc);
		Tile* GetTileAtGridPosition(int x, int y) const;
		Tile* GetTileForPacman();

		Tile* GetTileForBlinky();
		Tile* GetTileForSpeedy();
		Tile* GetTileForBashful();
		Tile* GetTileForPokey();

		Tile* GetTileForExitLeft() const;
		Tile* GetTileForExitRight();


		CL_Pointf* GetScatterPositionForShadow();
		CL_Pointf* GetScatterPositionForSpeedy();
		CL_Pointf* GetScatterPositionForBashful();
		CL_Pointf* GetScatterPositionForPokey();
		void Render();
		~Level(void);
	};
}
