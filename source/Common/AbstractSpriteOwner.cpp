#include "AbstractSpriteOwner.h"
#include "Desktop.h"
#include "ISprite.h"

AbstractSpriteOwner::AbstractSpriteOwner(): zOrder() {}

AbstractSpriteOwner::~AbstractSpriteOwner() {
	for (ZIter p = zOrder.begin(); p != zOrder.end(); ++p) {
		if (p->second->decrementUsage()) {
			delete p->second;
		}
	}
}

void AbstractSpriteOwner::addSprite(AbstractScreenObject* sprite, int z) {
	sprite->incrementUsage();
	zOrder.insert(ZPair(z, sprite));
}

bool AbstractSpriteOwner::setZOrder(AbstractScreenObject* sprite, int z) {
	for (ZIter p = zOrder.begin(); p != zOrder.end(); ++p) {
		if (p->second == sprite) {
			zOrder.erase(p);
			zOrder.insert(ZPair(z, sprite));
			return true;
		}
	}
	return false;
}

int AbstractSpriteOwner::getDesktopWidth() {
	return desktop.getWidth();
}

int AbstractSpriteOwner::getDesktopHeight() {
	return desktop.getHeight();
}

void AbstractSpriteOwner::update(uint64 timestamp) {
	for (ZIter p = zOrder.begin(); p != zOrder.end(); ++p) {
		p->second->update(timestamp);
	}
}

void AbstractSpriteOwner::refresh() {
	for (ZIter p = zOrder.begin(); p != zOrder.end(); ++p) {
		p->second->refresh();
	}
}

bool AbstractSpriteOwner::sendMessage(int msg, int x, int y) {
	for (RIter p = zOrder.rbegin(); p != zOrder.rend(); ++p) {
		if (p->second->isBackground()) continue;
		if (p->second->sendMessage(msg, x, y)) {
			return true;
		}
	}
	return false;
}

void AbstractSpriteOwner::unload() {
	for (ZIter p = zOrder.begin(); p != zOrder.end(); ++p) {
		p->second->unload();
	}
}
