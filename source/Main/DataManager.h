#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#define FILE_NAME "props.cfg"

#include "s3eFile.h"

enum EDataProperty {
	edpSoundOn                = 0,
	edpMusicOn                = 1,
	SLOTS_CNT                 = 2
};

class DataManager {
	public:
		DataManager(): isModified(false), IsInitialized(false) {}
		void init();
		void release();
		void flush();
		int  getValue(int propId);
		void setValue(int propId, int propValue);
		void setMinValue(int propId, int propValue);
		void setMaxValue(int propId, int propValue);
		const char* getError() {return error;}
		void  setInitialized() {IsInitialized = true;}
		bool  isInitialized() const {return IsInitialized;}
	private:
		bool load();
		void initialize();
		bool isModified;
		void checkError();
		int32 data[SLOTS_CNT];
		const char* error;
		bool  IsInitialized;
};

extern DataManager dm;
        
#endif	// _DATAMANAGER_H_
