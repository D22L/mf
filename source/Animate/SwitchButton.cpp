#include "SwitchButton.h"
#include "Desktop.h"
#include "MoveAction.h"
#include "SendMessageAction.h"
#include "SoundAction.h"
#include "DataManager.h"

SwitchButton::SwitchButton(ISpriteOwner* scene, int x, int y, int zOrder): Button(scene, x, y, zOrder), dataId(-1) {
	SwitchButton::configure();
}

void SwitchButton::setDataId(int id) {
	dataId = id;
	state = dm.getValue(id);
}

void SwitchButton::configure() {
	msgUp->addAction(new SendMessageAction(this, 50, emtSwitch));
}

bool SwitchButton::sendMessage(int msg, uint64 timestamp, void* data) {
	if (msg == emtSwitch) {
		doMessage(msg, 0, timestamp);
		if (receiver != NULL) {
			receiver->sendMessage(message, 0, (IObject*)this);
		}
		if (dataId >= 0) {
			dm.setValue(dataId, state);
		}
		return true;
	}
	return Button::sendMessage(msg, timestamp, data);
}
