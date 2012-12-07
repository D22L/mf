#ifndef _ISPRITE_H_
#define _ISPRITE_H_

#include "Locale.h"

#include "Iw2D.h"
#include "IwGx.h"

class ISprite {
	public:
		virtual void addImage(const char* res, int state = 0, int locale = 0) = 0;
		virtual CIw2DImage* getImage(int state = 0)                           = 0;
};

#endif	// _ISPRITE_H_
