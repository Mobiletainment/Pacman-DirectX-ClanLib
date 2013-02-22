/*
	Autor: Patrick Schwarz
	Restricted Use: Only for Students of the FH Technikum Wien - Games Engineering 2012
*/

#include "precomp.h"
#include "SpriteManager.h"

map<string, CL_Sprite*> SpriteManager::_spriteCache;

 CL_Sprite* SpriteManager::LoadSprite(CL_GraphicContext& gc, const string& spritePath)
 {
	 if(_spriteCache.count(spritePath)<=0)
	 {
		CL_SpriteDescription spriteDescription;
		spriteDescription.add_frame(CL_PNGProvider::load(spritePath));
		CL_Sprite* sprite=new CL_Sprite(gc, spriteDescription);

		_spriteCache[spritePath]=sprite;
	 }

	return _spriteCache[spritePath];
 }
