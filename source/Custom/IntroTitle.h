#ifndef _INTROTITLE_H_
#define _INTROTITLE_H_

#include <string.h>
#include "CompositeSprite.h"

class IntroTitle: public CompositeSprite {
    public:
		IntroTitle(Scene* scene, int zOrder): CompositeSprite(scene, 0, 0, zOrder) {}
		virtual bool init();
		virtual void refresh();
};

#endif	// _INTROTITLE_H_
