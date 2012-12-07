#ifndef _ANIMATEACTION_H_
#define _ANIMATEACTION_H_

#include "s3eTypes.h"

#include "AbstractScreenObject.h"

class AnimateAction {
	private:
		uint64 startDelta;
		uint64 stopDelta;
	protected:
		AbstractScreenObject* sprite;
		virtual void doAction(int timeDelta) = 0;
		virtual int getTimeInterval() {return (int)(stopDelta - startDelta);}
	public:
		AnimateAction(AbstractScreenObject* sprite, uint64 startDelta, uint64 stopDelta);
		virtual ~AnimateAction() {}
		virtual bool isSheduled(uint64 timeDelta);
		virtual void update(uint64 timeDelta);
		virtual void clear() {}
};

#endif	// _ANIMATEACTION_H_
