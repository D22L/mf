#ifndef _LOCALE_H_
#define _LOCALE_H_

enum ELocale {
    elNothing       = 0x0,
	elImage         = 0x1,
	elSound         = 0x2,
    elEnImage       = 0x5,
    elRuImage       = 0x9,
    elEnSound       = 0x6,
    elRuSound       = 0xA
};

class Locale {
	public:
		static int getCurrentImageLocale();
		static int getCurrentSoundLocale();
		static int getCommonImageLocale() {return elNothing;}
		static int getCommonSoundLocale() {return elSound;}
		static const char* getGroupName(int locale);
};
        
#endif	// _LOCALE_H_
