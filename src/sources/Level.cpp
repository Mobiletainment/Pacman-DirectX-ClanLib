/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#include "precomp.h"
#include "Level.h"

using namespace KI;

string _levelInfo[]={
				"5111111111111ab1111111111116",
				"4............DB............2",
				"4.EAAF.EAAAF.DB.EAAAF.EAAF.2" ,
				"4*D  B.D   B.DB.D   B.D  B*2" ,
				"4.GCCH.GCCCH.GH.GCCCH.GCCH.2" ,
				"4..........................2" ,
				"4.EAAF.EF.EAAAAAAF.EF.EAAF.2" ,
				"4.GCCH.DB.GCCFECCH.DB.GCCH.2" ,
				"4......DB....DB....DB......2" ,
				"83333).DGAAF DB EAAHB.(33337" ,
				"     4.DECCH GH GCCFB.2     " ,
				"     4.DB          DB.2     " ,
				"     4.DB (3>--<3) DB.2     " ,
				"11111].GH 2      4 GH.[11111" ,
				"      .   2      4   .      " ,
				"33333).EF 2      4 EF.(33333" ,
				"     4.DB [111111] DB.2     " ,
				"     4.DB          DB.2     " ,
				"     4.DB EAAAAAAF DB.2     " ,
				"51111].GH GCCFECCH GH.[11116" ,
				"4............DB............2" ,
				"4.EAAF.EAAAF.DB.EAAAF.EAAF.2" ,
				"4.GCFB.GCCCH.GH.GCCCH.DECH.2" ,
				"4*..DB................DB..*2" ,
				"gAF.DB.EF.EAAAAAAF.EF.DB.EAc" ,
				"hCH.GH.DB.GCCFECCH.DB.GH.GCd" ,
				"4......DB....DB....DB......2" ,
				"4.EAAAAHGAAF.DB.EAAHGAAAAF.2" ,
				"4.GCCCCCCCCH.GH.GCCCCCCCCH.2" ,
				"4..........................2" ,
				"8333333333333333333333333337" ,
};

vector<Tile*> _tiles;
map<char, TileFactory*> _tileMapping;
Level::Level(CL_GraphicContext gc)
{
	_gc=gc;

	SizeY =sizeof(_levelInfo)/sizeof(string);
	SizeX =_levelInfo[0].length();

	_tileMapping['1'] = new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outerwall_top.png"));
	_tileMapping['2']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outerwall_right.png"));
	_tileMapping['3']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outerwall_bottom.png"));
	_tileMapping['4']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outerwall_left.png"));
	_tileMapping['5']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_top_left.png"));
	_tileMapping['6']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_top_right.png"));
	_tileMapping['7']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_bottom_right.png"));
	_tileMapping['8']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_bottom_left.png"));
	_tileMapping['(']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_narrow_top_left.png"));
	_tileMapping[')']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_narrow_top_right.png"));
	_tileMapping['[']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_narrow_bottom_left.png"));
	_tileMapping[']']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outercorner_narrow_bottom_right.png"));
	_tileMapping['>']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/gate_left.png"));
	_tileMapping['<']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/gate_right.png"));
	_tileMapping['-']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/door.png"));


	_tileMapping['A']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/wall_top.png"));
	_tileMapping['B']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/wall_right.png"));
	_tileMapping['C']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/wall_bottom.png"));
	_tileMapping['D']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/wall_left.png"));
	_tileMapping['E']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/corner_top_left.png"));
	_tileMapping['F']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/corner_top_right.png"));
	_tileMapping['G']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/corner_bottom_left.png"));
	_tileMapping['H']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/corner_bottom_right.png"));

	_tileMapping['a']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_top_left.png"));
	_tileMapping['b']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_top_right.png"));
	_tileMapping['c']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_right_top.png"));
	_tileMapping['d']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_right_bottom.png"));
	_tileMapping['e']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_bottom_left.png"));
	_tileMapping['f']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_bottom_right.png"));
	_tileMapping['g']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_left_top.png"));
	_tileMapping['h']= new WallTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/outernose_left_bottom.png"));

	_tileMapping[' ']= new WalkableTileFactory(NULL); //no image = freespace
	_tileMapping['.']= new EatableTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/dot.png"));
	_tileMapping['*']= new PillTileFactory(SpriteManager::LoadSprite(_gc, "resources/tiles/big_dot.png"));

	//Create Tiles
	for(unsigned int y=0;y<SizeY;y++)
	{
		string row=_levelInfo[y];
		for(unsigned int x=0;x<SizeX;x++)
		{
			char c=row[x];
			TileFactory* tileFactory=_tileMapping[c];
			Tile* tile=tileFactory->CreateTile(new CL_Pointf((float) x, (float)y));
			_tiles.push_back(tile);
		}
	}

	//Init Grid
	for(unsigned int y=0;y<SizeY;y++)
	{
		for(unsigned int x=0;x<SizeX;x++)
		{
		   Tile* tile=GetTileAtGridPosition(x,y);
		   
		   if(x>0)
		   {
			   tile->SetLeft(GetTileAtGridPosition(x-1, y));
		   }
		   else if(tile->Walkable)
		   {
			   tile->SetLeft(GetTileAtGridPosition(SizeX-1, y)); //Gate
		   }

		   if(y>0)
		   {
			   tile->SetTop(GetTileAtGridPosition(x, y-1));
		   }
		   else if(tile->Walkable)
		   {
			   tile->SetTop(GetTileAtGridPosition(x, SizeY-1));
		   }
		}
	}
}

/*
	Author: David Pertiller
*/

Tile* Level::GetTileForPacman()
{
	return GetTileAtGridPosition(10, 23);
}

Tile* Level::GetTileForBlinky()
{
	return GetTileAtGridPosition(26,1);
}

Tile* Level::GetTileForSpeedy()
{
	return GetTileAtGridPosition(1,1);
}

Tile* Level::GetTileForBashful()
{
	return GetTileAtGridPosition(26,29);
}

Tile* Level::GetTileForPokey()
{
	return GetTileAtGridPosition(1,29);
}

Tile* Level::GetTileForExitLeft() const
{
	return GetTileAtGridPosition(0,14);
}

Tile* Level::GetTileForExitRight()
{
	return GetTileAtGridPosition(27,14);
}

CL_Pointf* Level::GetScatterPositionForShadow()
{
	Tile* tile=GetTileAtGridPosition(SizeX-2, 0);
	return new CL_Pointf(tile->Position->x, tile->Position->y-tile->Size->height*3);
}

CL_Pointf* Level::GetScatterPositionForSpeedy()
{
	Tile* tile=GetTileAtGridPosition(2, 0);
	return new CL_Pointf(tile->Position->x, tile->Position->y-tile->Size->height*3);
}

CL_Pointf* Level::GetScatterPositionForBashful()
{
	Tile* tile=GetTileAtGridPosition(SizeX-1, SizeY-1);
	return new CL_Pointf(tile->Position->x, tile->Position->y+tile->Size->height*2);
}

CL_Pointf* Level::GetScatterPositionForPokey()
{
	Tile* tile=GetTileAtGridPosition(0, SizeY-1);
	return new CL_Pointf(tile->Position->x, tile->Position->y+tile->Size->height*2);
}

Tile* Level::GetTileAtGridPosition(int x, int y) const
{
	return _tiles[(y*SizeX+x)];
}

void Level::Render()
{
	for(unsigned int i=0;i<_tiles.size();i++)
	{
		_tiles[i]->Render(&_gc);
	}
}


Level::~Level(void)
{
}
