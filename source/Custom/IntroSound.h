#ifndef _INTROSOUND_H_
#define _INTROSOUND_H_

#include "CompositeSprite.h"

class IntroSound: public CompositeSprite {
    private:
		Scene* scene;
    public:
		IntroSound(Scene* scene, int zOrder): CompositeSprite(scene, 0, 0, zOrder), scene(scene) {}
		virtual bool init();
};

#endif	// _INTROSOUND_H_
