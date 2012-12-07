#include "SendMessageAction.h"

SendMessageAction::SendMessageAction(AbstractScreenObject* sprite, uint64 timeDelta, 
									 int msg, void* data): AnimateAction(sprite, timeDelta, timeDelta)
									 , msg(msg), data(data) {}

void SendMessageAction::doAction(int timeDelta) {
	sprite->sendMessage(msg, 0, data);
}
