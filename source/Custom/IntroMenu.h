#ifndef _INTROMENU_H_
#define _INTROMENU_H_

#include "CompositeSprite.h"
#include "Button.h"

class IntroMenu: public CompositeSprite {
    private:
		Scene* scene;
		Button* firstButton;
		Button* secondButton;
    public:
		IntroMenu(Scene* scene, int zOrder): CompositeSprite(scene, 0, 0, zOrder), scene(scene) {}
		virtual bool init();
};

#endif	// _INTROMENU_H_
