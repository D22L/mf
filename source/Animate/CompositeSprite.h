#ifndef _COMPOSITESPRITE_H_
#define _COMPOSITESPRITE_H_

#include "AnimatedSprite.h"
#include "AbstractSpriteOwner.h"
#include "Scene.h"

class CompositeSprite: public AnimatedSprite
	                 , public AbstractSpriteOwner {
	protected:
		ISpriteOwner* owner;	
	public:
		CompositeSprite(ISpriteOwner* scene, int x, int y, int zOrder);
		virtual int  getXSize(int xSize);
		virtual int  getYSize(int ySize);
		virtual int  getXPos(int x);
		virtual int  getYPos(int y);
		virtual bool setState(int newState);
		virtual void refresh();
		virtual void update(uint64 timestamp, bool isPaused);
		virtual bool isBuzy();
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL);
		virtual bool sendMessage(int msg, int x, int y);
		virtual void unload();
		virtual void addPauseDelta(uint64 pauseDelta);
};

#endif	// _COMPOSITESPRITE_H_
