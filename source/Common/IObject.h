#ifndef _IOBJECT_H_
#define _IOBJECT_H_

#include "s3e.h"

class IObject {
	public:
		virtual ~IObject() {}   
		virtual bool isBuzy()                                                      = 0;
		virtual int  getState()                                                    = 0;
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL) = 0;
		virtual bool sendMessage(int msg, int x, int y)                            = 0;
		virtual void update(uint64 timestamp)                                      = 0;
		virtual void refresh()                                                     = 0;
		virtual void unload()                                                      = 0;
};

#endif	// _IOBJECT_H_
