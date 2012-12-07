#ifndef _ABSTRACTSCREENOBJECT_H_
#define _ABSTRACTSCREENOBJECT_H_

#include <string>
#include "Iw2D.h"

#include "IScreenObject.h"

using namespace std;

class AbstractScreenObject: public IScreenObject {
	private:
		static int idCounter;
		int id;
		int usageCounter;
	protected:
		virtual bool init();
		CIw2DAlphaMode alpha;
		int xPos, yPos, angle;
		int xDelta, yDelta;
		bool isVisible;
		bool isInitialized;
	public:
		AbstractScreenObject(int x, int y);
		virtual ~AbstractScreenObject() {}   
		int getId() const {return id;}
		void incrementUsage();
		bool decrementUsage();
		int getXDelta() const {return xDelta;}
		int getYDelta() const {return yDelta;}
		virtual int  getXPos()      {return xPos + xDelta;}
		virtual int  getYPos()      {return yPos + yDelta;}
		virtual int  getWidth()     {return 0;} // TODO:
		virtual int  getHeight()    {return 0;} // TODO:
		virtual bool isBackground() {return false;}
		virtual bool isBuzy()       {return false;}
		int  getAngle() const {return angle;}
		void move(int x = 0, int y = 0);
		void setXY(int x = 0, int y = 0);
		void setDeltaXY(int x = 0, int y = 0);
		void setAngle(int a) {angle = a;}
		void setAlpha(CIw2DAlphaMode a) {alpha = a;}
		virtual bool setState(int state) {return false;}
		void setName(string name);
		static IObject* getName(string name);
};

#endif	// _ABSTRACTSCREENOBJECT_H_
