#include "Button.h"
#include "Desktop.h"
#include "MoveAction.h"
#include "SendMessageAction.h"
#include "SoundAction.h"

Button::Button(ISpriteOwner* scene, const char* res, int x, int y, int zOrder, int loc): AnimatedSprite(scene, res, x, y, zOrder, loc), receiver(NULL) {
	Button::configure();
}

Button::Button(ISpriteOwner* scene, int x, int y, int zOrder): AnimatedSprite(scene, x, y, zOrder), receiver(NULL) {
	Button::configure();
}

void Button::configure() {
	msgDown = new AnimateMessage();
	msgDown->addAction(new MoveAction(this, 0, 50, 10, 10));
	msgDown->addAction(new SoundAction(this, 50, "menubutton"));
	addMessageRule(ebmDown, msgDown);
	msgUp = new AnimateMessage();
	msgUp->addAction(new MoveAction(this, 100, 150, 0, 0));
	addMessageRule(ebmOutUp, msgUp);
	msgUp = new AnimateMessage();
	msgUp->addAction(new MoveAction(this, 100, 150, 0, 0));
	msgUp->addAction(new SendMessageAction(this, 100, ebmPressed));
	msgUp->addAction(new SendMessageAction(this, 110, emtInit));
	addMessageRule(ebmUp, msgUp);
}

bool Button::isValidMessage(int msg) {
	switch (msg) {
		case emtTouchDown:
		case   emtTouchUp:
		case      ebmDown:
		case        ebmUp: 
		case     ebmOutUp: 
		case   ebmPressed: return true;
		default: return AnimatedSprite::isValidMessage(msg);
	}
}

void Button::doMessage(int msg, void* data, uint64 timestamp) {
	if (msg == ebmPressed) {
		if (receiver != NULL) {
			receiver->sendMessage(message, 0, (IObject*)this);
		}
		return;
	}
	AnimatedSprite::doMessage(msg, data, timestamp);
}

bool Button::sendMessage(int msg, uint64 timestamp, void* data) {
	if ((msg & emtTouchEvent) != 0) {
		switch (msg & emtTouchMask) {
			case emtTouchDown:
				sendMessage(ebmDown, desktop.getCurrentTimestamp());
				break;
			case emtTouchUp:
				sendMessage(ebmUp, desktop.getCurrentTimestamp());
                break;
			case emtTouchOutUp:
				sendMessage(ebmOutUp, desktop.getCurrentTimestamp());
				break;
		}
		return true;
	}
	return AnimatedSprite::sendMessage(msg, timestamp, data);
}

void Button::addReceiver(int m, AbstractSpriteOwner* r) {
	message  = m;
	receiver = r;
}
