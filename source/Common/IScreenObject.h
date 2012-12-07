#ifndef _ISCREENOBJECT_H_
#define _ISCREENOBJECT_H_

#include "s3e.h"

#include "IObject.h"

class IScreenObject: public IObject {
	public:
		virtual int  getXPos()    = 0;
		virtual int  getYPos()    = 0;
		virtual int  getWidth()   = 0;
		virtual int  getHeight()  = 0;
};

#endif	// _ISCREENOBJECT_H_
