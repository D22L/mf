#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#if defined IW_DEBUG
#define LOAD_ALL_GROUPS true
#else
#define LOAD_ALL_GROUPS false
#endif

#include <map>
#include <string>

#include "s3e.h"
#include "IwResManager.h"
#include "IwSound.h"

#include "ResourceHolder.h"

using namespace std;

class ResourceManager {
	private:	
		map<string, ResourceHolder*> res;
	public:
		ResourceManager(): res() {}
		void init();
		void release();
		ResourceHolder* load(const char* name, int loc, bool isUnloaded = false);

	typedef map<string, ResourceHolder*>::iterator RIter;
	typedef pair<string, ResourceHolder*> RPair;
};

extern ResourceManager rm;
        
#endif	// _RESOURCEMANAGER_H_
