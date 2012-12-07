#include "Locale.h"
#include "s3e.h"

const char* Locale::getGroupName(int locale) {
	switch (locale) {
		case   elImage: return "images";
		case elEnSound:
		case elRuSound:
		case   elSound: return "sounds";
		case elEnImage: return "locale_en";
		case elRuImage: return "locale_ru";
		       default: return NULL;
	}
}

int Locale::getCurrentImageLocale() {
	int32 lang = s3eDeviceGetInt(S3E_DEVICE_LANGUAGE);
	switch (lang) {
		case S3E_DEVICE_LANGUAGE_RUSSIAN: return elRuImage;
		default: return elEnImage;
	}
}

int Locale::getCurrentSoundLocale() {
	int32 lang = s3eDeviceGetInt(S3E_DEVICE_LANGUAGE);
	switch (lang) {
		case S3E_DEVICE_LANGUAGE_RUSSIAN: return elRuSound;
		default: return elEnSound;
	}
}
