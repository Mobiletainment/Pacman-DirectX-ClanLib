#pragma once
#include "Tile.h"
#include "SpriteManager.h"
#include <string>
using namespace std;

namespace KI
{
class Character
{
	private:
		CL_GraphicContext _gc;
		static const float _frameSize;
		int _currentFrame;
		int _elapsedFrames;
		void CheckAnimation();
	protected:
		int _startFrame;
		int _endFrame;
		float _walkSpeed;
		Tile* _currentTile;
		Tile* _targetTile;
		CL_Sprite* _sprite;
		Direction _currentDirection;
		Direction _nextDirection;
		void SetFrame(int frame);
		void SetFrames(int startFrame, int endFrame);
		virtual void SetCurrentDirection(Direction direction);
		void MoveInDirection(const Direction &direction);
	public:
		CL_Pointf* Position;
		Direction CurrentDirection();
		Tile *CurrentTile() const;
		Character(CL_GraphicContext& gc, Tile* startingTile, string spritePath);
		virtual void Update();
		void Render();
		void Move(Direction direction);
		~Character(void);
	};
}
