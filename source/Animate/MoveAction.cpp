#include "MoveAction.h"

MoveAction::MoveAction(AbstractScreenObject* sprite, uint64 startDelta, uint64 stopDelta, 
					   int x, int y): AnimateAction(sprite, startDelta, stopDelta)
					   , x(x), y(y), isCleared(true) {}

MoveAction::MoveAction(AbstractScreenObject* sprite, uint64 delta, 
					   int x, int y): AnimateAction(sprite, delta, delta)
					   , x(x), y(y), isCleared(true) {}

void MoveAction::doAction(int timeDelta) {
	if (isCleared) {
		startX = sprite->getXDelta();
		startY = sprite->getYDelta();
		isCleared = false;
	}
	int timeInterval = getTimeInterval();
    if (timeInterval <= 0) {
		sprite->setDeltaXY(x, y);
    } else if (timeDelta > timeInterval) {
		sprite->setDeltaXY(x, y);
	} else {
		int xInterval = x - startX;
		int yInterval = y - startY;
		int xDelta = (xInterval * timeDelta) / timeInterval;
		int yDelta = (yInterval * timeDelta) / timeInterval;
		sprite->setDeltaXY(startX + xDelta, startY + yDelta);
	}
}
