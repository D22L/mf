#include "IntroSound.h"
#include "SwitchButton.h"
#include "Button.h"
#include "Intro.h"
#include "Locale.h"
#include "DataManager.h"

bool IntroSound::init() {
	if (!AbstractScreenObject::init()) return false;
	setXY(346, 227);
	SwitchButton* s = new SwitchButton(this, 0, 0, 1);
		s->addImage("musicoff", 0, Locale::getCurrentImageLocale());
		s->addImage("musicon", 1, Locale::getCurrentImageLocale());
		s->setName("musicon");
#if defined IW_DEBUG
		s->setState(0);
#else
		s->setState(1);
#endif
		s->setDataId(edpMusicOn);
	s->addReceiver(eimCheckMusic, scene);
	s = new SwitchButton(this, 0, 157, 2);
		s->addImage("soundoff", 0, Locale::getCurrentImageLocale());
		s->addImage("soundon", 1, Locale::getCurrentImageLocale());
		s->setName("soundon");
		s->setState(1);
		s->setDataId(edpSoundOn);
	Button* b = new Button(this, "back.png", -300, 350, 3, Locale::getCommonImageLocale());
	b->addReceiver(eimBack, scene);
    return true;
}
