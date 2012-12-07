#ifndef _SWITCHBUTTON_H_
#define _SWITCHBUTTON_H_

#include "Button.h"

enum ESwitchButtonMessage {
	esmPressed          = 0x0102
};

class SwitchButton: public Button {
	private:
		int dataId;
	protected:
		void configure();
	public:
		SwitchButton(ISpriteOwner* scene, int x, int y, int zOrder = 0);
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL);
		void setDataId(int id);
};

#endif	// _SWITCHBUTTON_H_
