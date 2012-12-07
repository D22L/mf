#ifndef _INTRO_H_
#define _INTRO_H_

#include "Scene.h"
#include "CompositeSprite.h"

enum EIntroMessage {
		eimPlay              = 0x100,
		eimSettings          = 0x101,
		eimBack              = 0x102,
		eimCheckMusic        = 0x103
};

enum EIntroStatus {
		eisMain              = 0,
		eisSettings          = 1
};

class Intro: public Scene {
	private:
		Sprite* background;
		CompositeSprite* title;
		CompositeSprite* menu;
		CompositeSprite* settings;
		int state;
		void checkMusic();
    protected:
		virtual bool doKeyMessage(int msg, s3eKey key);
		virtual int  getState() {return state;}
		void setState(int s) {state = s;}
	public:
		Intro();
		virtual bool init();
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL);
};

extern Intro* introScene;

#endif	// _INTRO_H_
