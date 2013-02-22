/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#pragma once
#include <string>
#include <map>
using namespace std;

class SpriteManager
{
public:
	static CL_Sprite* LoadSprite(CL_GraphicContext& gc, const string& spritePath);
private:
	static map<string, CL_Sprite*> _spriteCache;
};

