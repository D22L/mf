#ifndef _SOUNDACTION_H_
#define _SOUNDACTION_H_

#include <string>
#include "IwSound.h"

#include "AnimateAction.h"
#include "Locale.h"

using namespace std;

class SoundAction: public AnimateAction {
	private:
		string res;
		int loc;
		bool checkSound();
	protected:
		virtual void doAction(int timeDelta);
	public:
		SoundAction(AbstractScreenObject* sprite, uint64 timeDelta, const char* r, int loc = elSound);
};

#endif	// _SOUNDACTION_H_
