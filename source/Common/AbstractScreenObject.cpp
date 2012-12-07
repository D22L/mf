#include "AbstractScreenObject.h"
#include "Desktop.h"

int AbstractScreenObject::idCounter = 0;

AbstractScreenObject::AbstractScreenObject(int x, int y): xPos(x), alpha(IW_2D_ALPHA_NONE),
yPos(y), angle(0), xDelta(0), yDelta(0), isVisible(true), isInitialized(false), usageCounter(0) {
	id = ++idCounter;
}

void AbstractScreenObject::setName(string name) {
	desktop.setName(name, (IObject*)this);
}

IObject* AbstractScreenObject::getName(string name) {
	return (IObject*)desktop.getName(name);
}

bool AbstractScreenObject::init() {
	bool r = !isInitialized;
	isInitialized = true;
	return r;
}

void AbstractScreenObject::incrementUsage() {
	usageCounter++;
}

bool AbstractScreenObject::decrementUsage() {
	usageCounter--;
	return (usageCounter == 0);
}

void AbstractScreenObject::move(int x, int y) {
	xDelta += x;
	yDelta += y;
}

void AbstractScreenObject::setDeltaXY(int x, int y) {
	xDelta = x;
	yDelta = y;
}

void AbstractScreenObject::setXY(int x, int y) {
	xPos = x;
	yPos = y;
}
