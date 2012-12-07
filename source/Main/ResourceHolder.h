#ifndef _RESOURCEHOLDER_H_
#define _RESOURCEHOLDER_H_

#include <string>

#include "s3e.h"
#include "Iw2D.h"
#include "IwResManager.h"

using namespace std;

class ResourceHolder {
	private:
		string name;
		int loc;
		CIw2DImage* data;
	public:
		ResourceHolder(const char* name, int loc);
	   ~ResourceHolder() {unload();}
		void load();
		void unload();
		CIw2DImage* getData();
};
        
#endif	// _RESOURCEHOLDER_H_
