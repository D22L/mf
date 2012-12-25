#ifndef _ABSTRACTSPRITEOWNER_H_
#define _ABSTRACTSPRITEOWNER_H_

#include <map>

#include "IObject.h"
#include "ISpriteOwner.h"
#include "AbstractScreenObject.h"

using namespace std;

class AbstractSpriteOwner: public ISpriteOwner {
	protected:
		multimap<int, AbstractScreenObject*> zOrder;
	public:
		AbstractSpriteOwner();
		virtual ~AbstractSpriteOwner();
		virtual void addSprite(AbstractScreenObject* sprite, int z);
		virtual bool setZOrder(AbstractScreenObject* sprite, int z);
		virtual int  getDesktopWidth();
		virtual int  getDesktopHeight();
		virtual int  getState() {return 0;}
		virtual void update(uint64 timestamp, bool isPaused);
		virtual void refresh();
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL) {return false;}
		virtual bool sendMessage(int msg, int x, int y);
		virtual void unload();
		virtual void correctPauseDelta(uint64 pauseDelta);

	typedef multimap<int, AbstractScreenObject*>::iterator ZIter;
	typedef multimap<int, AbstractScreenObject*>::reverse_iterator RIter;
	typedef pair<int, AbstractScreenObject*> ZPair;
};

#endif	// _ABSTRACTSPRITEOWNER_H_
