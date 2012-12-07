#ifndef _SCENE_H_
#define _SCENE_H_

#include <map>
#include <set>
#include "s3eKeyboard.h"

#include "AbstractSpriteOwner.h"
#include "AbstractScreenObject.h"

using namespace std;

class Scene: public AbstractSpriteOwner {
	private:
		AbstractScreenObject* background;
		map<s3eKey, int> keys;
		bool isInitialized;
        uint64 lastTime;
	protected:
		virtual bool doKeyMessage(int msg, s3eKey key) {return false;}
		virtual void regKey(s3eKey key);
	public:
		Scene();
	    virtual bool init();
		int getXSize(int xSize);
		int getYSize(int ySize);
		virtual int getXPos(int x) {return x;}
		virtual int getYPos(int y) {return y;}
		virtual void refresh();
		virtual void update(uint64 timestamp);
		virtual bool isBuzy() {return false;}
		virtual bool sendMessage(int id, int x, int y);

	typedef map<s3eKey, int>::iterator KIter;
	typedef pair<s3eKey, int> KPair;
};

#endif	// _SCENE_H_
