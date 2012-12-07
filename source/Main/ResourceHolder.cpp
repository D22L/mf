#include "ResourceHolder.h"
#include "Locale.h"

ResourceHolder::ResourceHolder(const char* name, int loc): name(name)
											   , loc(loc)
											   , data(NULL) {
}

void ResourceHolder::load() {
	if (data == NULL) {
		CIwResGroup* resGroup;
		const char* groupName = Locale::getGroupName(loc);
		if (groupName != NULL) {
			resGroup = IwGetResManager()->GetGroupNamed(groupName);
			IwGetResManager()->SetCurrentGroup(resGroup);
			data = Iw2DCreateImageResource(name.c_str());
		} else {
			data = Iw2DCreateImage(name.c_str());
		}
	}
}

void ResourceHolder::unload() {
	if (data != NULL) {
		delete data;
		data = NULL;
	}
}

CIw2DImage* ResourceHolder::getData() {
	load();
	return data;
}
