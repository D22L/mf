#include "Intro.h"
#include "Background.h"
#include "IntroTitle.h"
#include "IntroMenu.h"
#include "IntroSound.h"
#include "Desktop.h"

Intro* introScene = NULL;

Intro::Intro(): state(eisMain) {
    introScene = this;
}

bool Intro::init() {
	if (!Scene::init()) return false;
	regKey(s3eKeyBack);
	regKey(s3eKeyAbsBSK);
#if defined IW_DEBUG
    regKey(s3eKeyLSK);
#endif
	background = new Background(this, "background.png", 1);
	title = new IntroTitle(this, 2);
	menu = new IntroMenu(this, 3);
	settings = new IntroSound(this, 4);
	settings->doMessage(emtHide);
	checkMusic();
    return true;
}

bool Intro::doKeyMessage(int msg, s3eKey key) {
     if (msg == emtKeyPressed) {
	    switch (state) {
		    case eisSettings:
			    sendMessage(eimBack);
			    return true;
	    }
    }
    return false;
}

bool Intro::sendMessage(int msg, uint64 timestamp, void* data) {
	switch (msg) {
		case eimPlay:
			// TODO:
            return true;
		case eimSettings:
			background->setAlpha(IW_2D_ALPHA_HALF);
			title->doMessage(emtHide);
			menu->doMessage(emtHide);
			settings->doMessage(emtShow);
			setState(eisSettings);
			return true;
		case eimBack:
			background->setAlpha(IW_2D_ALPHA_NONE);
			title->doMessage(emtShow);
			menu->doMessage(emtShow);
			settings->doMessage(emtHide);
			setState(eisMain);
			return true;
        case emtInit:
		case eimCheckMusic:
			checkMusic();
			return true;
	}
	return false;
}

void Intro::checkMusic() {
	bool f = false;
	IObject* o = (IObject*)desktop.getName("musicon");
    if (o == NULL) {
		desktop.stopMusic();
        return;
    }
	f = (o->getState() != 0);
	if (f) {
		desktop.startMusic("music.mp3");
	} else {
		desktop.stopMusic();
	}
}
