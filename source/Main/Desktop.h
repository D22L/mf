#ifndef _DESKTOP_H_
#define _DESKTOP_H_

#include <set>
#include <map>
#include <string>
#include "s3eKeyboard.h"
#include "Scene.h"

using namespace std;

enum EMessageType {
	emtNothing                                                      = 0x00,

	emtHide                                                         = 0x01,
	emtShadow                                                       = 0x02,
	emtShow                                                         = 0x03,
	emtSwitch                                                       = 0x04,
	emtInit                                                         = 0x05,
	emtFix                                                          = 0x08,

	emtStartAnimation                                               = 0x06,
	emtStopAnimation                                                = 0x07,
	emtActivate                                                     = 0x09,

	emtSystemMessage                                                = 0x0F,

	emtTouchEvent                                                   = 0x10,
	emtTouchIdMask                                                  = 0x03,
    emtTouchMask                                                    = 0x78,
    emtMultiTouch                                                   = 0x14,
    emtTouchOut                                                     = 0x18,
	emtTouchDown                                                    = 0x30,
	emtTouchUp                                                      = 0x50,
	emtTouchOutUp                                                   = 0x58,
	emtTouchMove                                                    = 0x70,
	emtSingleTouchDown                                              = 0x30,
	emtSingleTouchUp                                                = 0x50,
	emtSingleTouchMove                                              = 0x70,
	emtMultiTouchDown                                               = 0x34,
	emtMultiTouchUp                                                 = 0x54,
	emtMultiTouchMove                                               = 0x74,

	emtKeyEvent                                                     = 0x80,
	emtKeyAction                                                    = 0x82,
	emtKeyDown                                                      = 0x81,
	emtKeyPressed                                                   = 0x83,
	emtKeyReleased                                                  = 0x82
};

class Desktop {
	private:
		static int32 ScreenSizeChangeCallback(void* systemData, void* userData);
		int width, height;
		bool isChanged;
		Scene* currentScene;
		bool isKeyAvailable;
		bool IsQuitMessageReceived;
        bool checkBounce(int id, int msg);
		void getScreenSizes();
        uint64 currentTimestamp;
	public:
        Desktop(): touches(), names(), currentScene(NULL) {}
		void init();
		void release();
		void update(uint64 timestamp);
		void refresh();
		int getWidth() const {return width;}
		int getHeight() const {return height;}
		Scene* getScene() {return currentScene;}
        uint64 getCurrentTimestamp() const {return currentTimestamp;}
		void setScene(Scene* scene);
		void sendQuitMessage() {IsQuitMessageReceived = true;}
		bool isQuitMessageReceived();
		void setName(string name, void* o);
		void* getName(string name);
		void startMusic(const char* res);
		void stopMusic();
        set<int> touches;
		map<string, void*> names;

    typedef set<int>::iterator TIter;
    typedef map<string, void*>::iterator NIter;
	typedef pair<string, void*> NPair;
};
        
extern Desktop desktop;

#endif	// _DESKTOP_H_
