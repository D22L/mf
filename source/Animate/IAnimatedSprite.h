#ifndef _IANIMATEDSPRITE_H_
#define _IANIMATEDSPRITE_H_

#include <string>

#include "Desktop.h"

using namespace std;

class IAnimatedSprite {
	public:
		virtual bool isValidMessage(int msg)                                     = 0;
		virtual void doMessage(int msg, void* data = NULL, uint64 timestamp = 0) = 0;
};

#endif	// _IANIMATEDSPRITE_H_
