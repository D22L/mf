#ifndef _ANIMATEMESSAGE_H_
#define _ANIMATEMESSAGE_H_

#include <set>
#include "s3eTypes.h"

#include "AnimateAction.h"

using namespace std;

class AnimateMessage {
	private:
		set<AnimateAction*> actions;
	public:
		AnimateMessage();
	   ~AnimateMessage();
		bool update(uint64 newDelta, uint64 oldDelta);
		void addAction(AnimateAction* action) {actions.insert(action);}

	typedef set<AnimateAction*>::iterator AIter;
};

#endif	// _ANIMATEMESSAGE_H_
