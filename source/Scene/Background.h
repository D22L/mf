#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Sprite.h"
#include "Locale.h"

class Background: public Sprite {
	public:
		Background(ISpriteOwner* owner, const char* res, int zOrder, int locale = elNothing);
		virtual bool isBackground() {return true;}
		virtual void refresh();
};

#endif	// _BACKGROUND_H_
