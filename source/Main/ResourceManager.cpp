#include "ResourceManager.h"
#include "Locale.h"

ResourceManager rm;

void ResourceManager::init() {
	IwResManagerInit();
#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CIwResHandlerWAV);
#endif
	IwGetResManager()->LoadGroup("sounds.group");
	if (LOAD_ALL_GROUPS || (Locale::getCurrentImageLocale() == elEnImage)) {
		IwGetResManager()->LoadGroup("locale_en.group");
	}
	if (LOAD_ALL_GROUPS || (Locale::getCurrentImageLocale() == elRuImage)) {
		IwGetResManager()->LoadGroup("locale_ru.group");
	}
}

void ResourceManager::release() {
	for (RIter p = res.begin(); p != res.end(); ++p) {
		delete p->second;
	}
	res.clear();
	IwResManagerTerminate();
	IwSoundTerminate();
}

ResourceHolder* ResourceManager::load(const char* name, int loc, bool isUnloaded) {
	ResourceHolder* r = NULL;
	string nm(name);
	RIter p = res.find(nm);
	if (p == res.end()) {
		switch (loc) {
			case elEnImage:
			case elRuImage: loc = Locale::getCurrentImageLocale();
		}
		r = new ResourceHolder(name, loc);
		res.insert(RPair(nm, r));
	} else {
		r = p->second;
	}
	if (!isUnloaded) {
		r->load();
	}
	return r;
}
