#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include <map>
#include <vector>

#include "Sprite.h"
#include "IAnimatedSprite.h"
#include "AnimateMessage.h"
#include "ResourceManager.h"

#define REFRESH_CNT 2

using namespace std;

class AnimatedSprite: public Sprite, 
	                  public IAnimatedSprite {
	protected:
		struct Message {
			Message(int id, uint64 timestamp, void* data = NULL): id(id), timestamp(timestamp), data(data) {}
			Message(const Message& m): id(m.id), timestamp(m.timestamp), data(m.data) {}
			int id;
			void* data;
			uint64 timestamp;
		};
		struct CurrentMessage {
			CurrentMessage(AnimateMessage* message, uint64 timestamp): message(message), timestamp(timestamp), lastTimeDelta(0), isEmpty(false) {}
			CurrentMessage(const CurrentMessage& m): message(m.message), timestamp(m.timestamp), lastTimeDelta(m.lastTimeDelta), isEmpty(m.isEmpty) {}
			AnimateMessage* message;
			uint64 timestamp;
			uint64 lastTimeDelta;
			bool isEmpty;
		};
		int state;
		map<int, ResourceHolder*> images;
		map<int, AnimateMessage*> rules;
		uint64 lastTimestamp;
		vector<Message> messages;
		vector<CurrentMessage> currentMessages;
		bool isAnimated;
		int refreshCnt;
	public:
		AnimatedSprite(ISpriteOwner* scene, int x, int y, int zOrder = 0);
		AnimatedSprite(ISpriteOwner* scene, const char* res, int x, int y, int zOrder = 0, int loc = elNothing);
	   ~AnimatedSprite();
        void clearMessageRules() {rules.clear();}
		void addMessageRule(int msg, AnimateMessage* rule);
		virtual void addImage(const char*res, int id = 0, int loc = 0);
		virtual CIw2DImage* getImage(int id = 0);
		virtual int  getState();
		virtual bool setState(int newState);
		virtual void update(uint64 timestamp, bool isPaused);
		virtual void refresh();
		virtual bool sendMessage(int msg, uint64 timestamp = 0, void* data = NULL);
		virtual bool isBuzy() {return false;}
		virtual bool isValidMessage(int msg) {return (msg <= emtSystemMessage);}
		virtual void doMessage(int msg, void* data = NULL, uint64 timestamp = 0);
		virtual void unload();
		virtual void addPauseDelta(uint64 pauseDelta);

	typedef map<int,  ResourceHolder*>::iterator IIter;
	typedef pair<int, ResourceHolder*> IPair;
	typedef map<int,  AnimateMessage*>::iterator RIter;
	typedef pair<int, AnimateMessage*> RPair;
	typedef vector<Message>::iterator MIter;
	typedef vector<CurrentMessage>::iterator CIter;
};

#endif	// _ANIMATEDSPRITE_H_
