#include "DataManager.h"

DataManager dm;

void DataManager::init() {
	initialize();
	load();
}

void DataManager::release() {
	flush();
}

void DataManager::initialize() {
	data[edpSoundOn]        = 1;
	data[edpMusicOn]        = 1;
}

int DataManager::getValue(int propId) {
	if (propId < SLOTS_CNT) {
		return data[propId];
	}
	return 0;
}

void DataManager::setValue(int propId, int propValue) {
	if (propId < SLOTS_CNT) {
		data[propId] = propValue;
		isModified = true;
	}
}

void DataManager::setMinValue(int propId, int propValue) {
	if (propId < SLOTS_CNT) {
		if ((data[propId] == 0)||(data[propId] > propValue)) {
			data[propId] = propValue;
			isModified = true;
		}
	}
}

void DataManager::setMaxValue(int propId, int propValue) {
	if (propId < SLOTS_CNT) {
		if ((data[propId] == 0)||(data[propId] < propValue)) {
			data[propId] = propValue;
			isModified = true;
		}
	}
}

void DataManager::checkError() {
	s3eFileGetError();
	error = s3eFileGetErrorString();
}

bool DataManager::load() {
	if (!s3eFileCheckExists(FILE_NAME)) return false;
	s3eFile* h = s3eFileOpen(FILE_NAME, "rb");
	if (h == NULL) {
		getError();
		return false;
	}
	int32 sz = s3eFileGetSize(h);
	if ((sz % sizeof(int32)) != 0) return false;
	sz = sz / sizeof(32);
	if (sz > SLOTS_CNT) {
		sz = SLOTS_CNT;
	}
	if (s3eFileRead((void*)data, sizeof(int32), sz, h) != sz) {
		initialize();
		checkError();
	}
	s3eFileClose(h);
	return true;
}

void DataManager::flush() {
	if (isModified) {
		s3eFile* h = s3eFileOpen(FILE_NAME, "wb");
		if (h == NULL) {
			checkError();
			return;
		}
		if (s3eFileWrite((const void*)data, sizeof(int32), SLOTS_CNT, h) != SLOTS_CNT) {
			checkError();
		}
		s3eFileClose(h);
		isModified = false;
	}
}
