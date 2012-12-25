#include "CompositeSprite.h"

CompositeSprite::CompositeSprite(ISpriteOwner* scene, int x, int y, int zOrder): AnimatedSprite(scene, x, y, zOrder) 
																		, owner(scene)
																		, AbstractSpriteOwner() {
}

void CompositeSprite::addPauseDelta(uint64 pauseDelta) {
	AbstractSpriteOwner::correctPauseDelta(pauseDelta);
	AnimatedSprite::addPauseDelta(pauseDelta);
}

int CompositeSprite::getXSize(int xSize) {
	return owner->getXSize(xSize);
}
		
int CompositeSprite::getYSize(int ySize) {
	return owner->getYSize(ySize);
}

int CompositeSprite::getXPos(int x) {
	return AbstractScreenObject::getXPos() + owner->getXPos(x);
}
	
int CompositeSprite::getYPos(int y) {
	return AbstractScreenObject::getYPos() + owner->getYPos(y);
}

void CompositeSprite::refresh() {
	if (isVisible) {
		init();
		AbstractSpriteOwner::refresh();
	}
}

void CompositeSprite::update(uint64 timestamp, bool isPaused) {
	AnimatedSprite::update(timestamp, isPaused);
	AbstractSpriteOwner::update(timestamp, isPaused);
}

bool CompositeSprite::isBuzy() {
	return AnimatedSprite::isBuzy();
}

bool CompositeSprite::sendMessage(int msg, uint64 timestamp, void* data) {
	return AnimatedSprite::sendMessage(msg, timestamp, data) ||
		owner->sendMessage(msg, timestamp, data);
}

bool CompositeSprite::sendMessage(int msg, int x, int y) {
	if (!isVisible) return false;
	return AbstractSpriteOwner::sendMessage(msg, x, y);
}

bool CompositeSprite::setState(int newState) {
    state = newState;
    return true;
}

void CompositeSprite::unload() {
	AbstractSpriteOwner::unload();
}
