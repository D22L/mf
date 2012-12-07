#ifndef _ISPRITEOWNER_H_
#define _ISPRITEOWNER_H_

#include "IObject.h"
#include "AbstractScreenObject.h"

class ISpriteOwner: public IObject {
	public:
		virtual void addSprite(AbstractScreenObject* sprite, int zOrder) = 0;
		virtual bool setZOrder(AbstractScreenObject* sprite, int z)      = 0;
		virtual int  getDesktopWidth()                                   = 0;
		virtual int  getDesktopHeight()                                  = 0;
		virtual int  getXSize(int xSize)                                 = 0;
		virtual int  getYSize(int ySize)                                 = 0;
		virtual int  getXPos(int x)                                      = 0;
		virtual int  getYPos(int y)                                      = 0;
};

#endif	// _ISPRITEOWNER_H_
