#include "AnimateMessage.h"

AnimateMessage::AnimateMessage(): actions() {}

AnimateMessage::~AnimateMessage() {
	for (AIter p = actions.begin(); p != actions.end(); ++p) {
		delete *p;
	}
}

bool AnimateMessage::update(uint64 newDelta, uint64 oldDelta) {
	bool r = false;
	for (AIter p = actions.begin(); p != actions.end(); ++p) {
		if ((*p)->isSheduled(oldDelta)) {
			r = true;
			(*p)->update(newDelta);
		} else {
			(*p)->clear();
		}
	}
	return r;
}
