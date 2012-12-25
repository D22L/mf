#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "AbstractScreenObject.h"
#include "ISprite.h"
#include "ISpriteOwner.h"
#include "Locale.h"
#include "ResourceManager.h"

class Sprite: public AbstractScreenObject 
            , public ISprite {
	protected:
		ISpriteOwner* owner;
		ResourceHolder* img;
		int capturedId;
	public:
		Sprite(ISpriteOwner* owner, int x, int y , int zOrder = 0);
		Sprite(ISpriteOwner* owner, const char* res, int x, int y, int zOrder = 0, int locale = elNothing);
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL);
		virtual bool sendMessage(int msg, int x, int y);
		virtual void update(uint64 timestamp, bool isPaused) {}
		virtual void refresh();
		virtual void addImage(const char*res, int state = 0, int locale = 0);
		virtual CIw2DImage* getImage(int id = 0);
		virtual int  getState()  {return 0;}
		virtual int  getWidth();
		virtual int  getHeight();
		virtual void unload();
};

#endif	// _SPRITE_H_
