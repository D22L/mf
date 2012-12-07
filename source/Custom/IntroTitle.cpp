#include "IntroTitle.h"
#include "Sprite.h"

bool IntroTitle::init() {
	if (!AbstractScreenObject::init()) return false;
	// Sprite settings
	setXY(122, 100);
	// Sprite components
	new Sprite(this, "sprite.png", 0, 0, 1);
    return true;
}

void IntroTitle::refresh() {
	CompositeSprite::refresh();
}
