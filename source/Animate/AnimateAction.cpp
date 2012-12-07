#include "AnimateAction.h"

AnimateAction::AnimateAction(AbstractScreenObject* sprite, uint64 startDelta,
							 uint64   stopDelta): sprite(sprite)
											    , startDelta(startDelta)
												, stopDelta(stopDelta) {
}

bool AnimateAction::isSheduled(uint64 timeDelta) {
	return timeDelta < stopDelta;
}

void AnimateAction::update(uint64 timeDelta) {
	if (timeDelta >= startDelta) {
		uint64 delta = timeDelta - startDelta;
		if (timeDelta > stopDelta) {
			delta = stopDelta - startDelta;
		}
		doAction((int)delta);
	}
}
