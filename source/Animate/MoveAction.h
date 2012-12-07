#ifndef _MOVEACTION_H_
#define _MOVEACTION_H_

#include "AnimateAction.h"

class MoveAction: public AnimateAction {
	private:
		int x, y;
		int startX, startY;
		bool isCleared;
	protected:
		virtual void doAction(int timeDelta);
		virtual void clear() {isCleared = true;}
	public:
		MoveAction(AbstractScreenObject* sprite, uint64 startDelta, uint64 stopDelta, int x, int y);
		MoveAction(AbstractScreenObject* sprite, uint64 delta, int x, int y);
};

#endif	// _MOVEACTION_H_
