#include "IntroMenu.h"
#include "Locale.h"
#include "Intro.h"
#include "Desktop.h"

bool IntroMenu::init() {
	if (!AbstractScreenObject::init()) return false;
	setXY(297, 384);
	firstButton = new Button(this, "play", 0, 0, 1, Locale::getCurrentImageLocale());
	firstButton->addReceiver(eimPlay, scene);
	secondButton = new Button(this, "setup", 0, 157, 2, Locale::getCurrentImageLocale());
	secondButton->addReceiver(eimSettings, scene);
    return true;
}
