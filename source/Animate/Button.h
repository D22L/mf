#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "AnimatedSprite.h"
#include "AbstractSpriteOwner.h"

enum EButtonMessage {
	ebmDown             = 0x0100,
	ebmUp               = 0x0101,
	ebmOutUp            = 0x0111,
	ebmPressed          = 0x0102
};

class Button: public AnimatedSprite {
	protected:
		AnimateMessage* msgDown;
		AnimateMessage* msgUp;
		int message;
		AbstractSpriteOwner* receiver;
		void configure();
	public:
		Button(ISpriteOwner* scene, const char* res, int x, int y, int zOrder = 0, int loc = elNothing);
		Button(ISpriteOwner* scene, int x, int y, int zOrder = 0);
		virtual bool isValidMessage(int msg);
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL);
		virtual void doMessage(int msg, void* data = NULL, uint64 timestamp = 0);
		virtual bool isPausable() const {return false;}
		void addReceiver(int m, AbstractSpriteOwner* r);
};

#endif	// _BUTTON_H_
