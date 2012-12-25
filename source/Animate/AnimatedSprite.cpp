#include "AnimatedSprite.h"
#include "Desktop.h"
#include "Locale.h"

AnimatedSprite::AnimatedSprite(ISpriteOwner* scene, int x, int y, int zOrder): Sprite(scene, x, y, zOrder)
                                            , state(0)
                                            , images()
											, lastTimestamp(0)
											, messages()
											, currentMessages()
											, isAnimated(false)
											, refreshCnt(REFRESH_CNT)
											, rules() {}

AnimatedSprite::AnimatedSprite(ISpriteOwner* scene, const char* res, int x, int y, int zOrder, int loc): Sprite(scene, x, y, zOrder)
                                            , state(0)
                                            , images()
											, lastTimestamp(0)
											, messages()
											, currentMessages()
											, isAnimated(false)
											, refreshCnt(REFRESH_CNT)
											, rules() {
	AnimatedSprite::addImage(res, 0, loc);
}

AnimatedSprite::~AnimatedSprite() {
	for (RIter p = rules.begin(); p != rules.end(); ++p) {
		delete p->second;
	}
}

void AnimatedSprite::unload() {
	for (IIter p = images.begin(); p != images.end(); ++p) {
		p->second->unload();
	}
}

void AnimatedSprite::addMessageRule(int msg, AnimateMessage* rule) {
	RIter p = rules.find(msg);
	if (p != rules.end()) {
		return;
	}
	rules.insert(RPair(msg, rule));
}

void AnimatedSprite::addImage(const char*res, int id, int loc) {
	ResourceHolder* img = rm.load(res, loc);
	images.insert(IPair(id, img));
}

bool AnimatedSprite::setState(int newState) {
	IIter p = images.find(newState);
	if (p == images.end()) {
		return false;
	}
	state = newState;
	return true;
}
		
CIw2DImage* AnimatedSprite::getImage(int id) {
	IIter p = images.find(id);
	if (p == images.end()) {
		return NULL;
	}
	return p->second->getData();
}

int AnimatedSprite::getState() {
	return state;
}

void AnimatedSprite::doMessage(int msg, void* data, uint64 timestamp) {
	init();
	int s = getState();
	switch (msg) {
		case emtStartAnimation:
			isAnimated = true;
			break;
		case emtStopAnimation:
			isAnimated = false;
			break;
		case emtSwitch:
			s++;
			if (getImage(s) == NULL) {
				s = 0;
			}
			setState(s);
			return;
		case emtHide: 
			isVisible = false;
			return;
		case emtShadow:
			isVisible = true;
			alpha = IW_2D_ALPHA_HALF;
			return;
		case emtShow: 
			isVisible = true;
			alpha = IW_2D_ALPHA_NONE;
			return;
	};
	if (timestamp == 0) {
		timestamp = s3eTimerGetMs();
	}
	RIter p = rules.find(msg);
	if (p != rules.end()) {
		for (CIter q = currentMessages.begin(); q != currentMessages.end(); ++q) {
			if (q->isEmpty) {
				q->isEmpty       = false;
				q->message       = p->second;
				q->timestamp     = timestamp;
				q->lastTimeDelta = 0;
				return;
			}
		}
		currentMessages.push_back(CurrentMessage(p->second, timestamp));
	}
}

bool AnimatedSprite::sendMessage(int msg, uint64 timestamp, void* data) {
	if (!isValidMessage(msg)) {
		return false;
	}
	if (timestamp <= lastTimestamp) {
		doMessage(msg, data);
		return true;
	}
	messages.push_back(Message(msg, timestamp, data));
	return true;
}

void AnimatedSprite::addPauseDelta(uint64 pauseDelta) {
	for (CIter p = currentMessages.begin(); p != currentMessages.end(); ++p) {
		p->timestamp += pauseDelta;
	}
}

void AnimatedSprite::update(uint64 timestamp, bool isPaused) {
	if (isPaused && isPausable()) return;
	bool isEmpty = true;
	for (MIter p = messages.begin(); p != messages.end(); ++p) {
		if (p->timestamp <= lastTimestamp) continue;
		if (p->timestamp <= timestamp) {
			doMessage(p->id, p->data, p->timestamp);
			continue;
		}
		isEmpty = false;
	}
	if (isEmpty) {
		messages.clear();
	}
	isEmpty = true;
	for (CIter p = currentMessages.begin(); p != currentMessages.end(); ++p) {
		if (p->isEmpty) continue;
		uint64 timeDelta = timestamp - p->timestamp;
		if (!p->message->update(timeDelta, p->lastTimeDelta)) {
			p->isEmpty = true;
			continue;
		}
		p->lastTimeDelta = timeDelta;
		isEmpty = false;
	}
	if (isEmpty) {
		currentMessages.clear();
	}
	lastTimestamp = timestamp;
}

void AnimatedSprite::refresh() {
	if (isAnimated) {
		if (--refreshCnt <= 0) {
			refreshCnt = REFRESH_CNT;
			doMessage(emtSwitch);
		}
	}
	Sprite::refresh();
}
