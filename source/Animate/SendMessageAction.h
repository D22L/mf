#ifndef _SENDMESSAGEACTION_H_
#define _SENDMESSAGEACTION_H_

#include "AnimateAction.h"

class SendMessageAction: public AnimateAction {
	private:
		int msg;
        void* data;
	protected:
		virtual void doAction(int timeDelta);
	public:
		SendMessageAction(AbstractScreenObject* sprite, uint64 timeDelta, int msg, void* data = NULL);
};

#endif	// _SENDMESSAGEACTION_H_
