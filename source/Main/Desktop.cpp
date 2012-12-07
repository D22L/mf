#include "Desktop.h"
#include "Iw2D.h"

#include "TouchPad.h"

Desktop desktop;

void Desktop::init() {
	IsQuitMessageReceived = false;
	getScreenSizes();
	setScene(NULL);
	isKeyAvailable = (s3eKeyboardGetInt(S3E_KEYBOARD_HAS_KEYPAD) || s3eKeyboardGetInt(S3E_KEYBOARD_HAS_ALPHA));
    s3eSurfaceRegister(S3E_SURFACE_SCREENSIZE, ScreenSizeChangeCallback, NULL);
}

void Desktop::release() {
    s3eSurfaceUnRegister(S3E_SURFACE_SCREENSIZE, ScreenSizeChangeCallback);
	touches.clear();
	names.clear();
}

int32 Desktop::ScreenSizeChangeCallback(void* systemData, void* userData) {
	desktop.isChanged = true;
	return 0;
}

void Desktop::setScene(Scene* scene) {
	if (scene != NULL) {
		scene->init();
	}
	currentScene = scene;
}

void Desktop::getScreenSizes() {
	width = Iw2DGetSurfaceWidth();
	height = Iw2DGetSurfaceHeight();
	isChanged = false;
}

void Desktop::setName(string name, void* o) {
	NIter p = names.find(name);
	if (p != names.end()) {
		names.erase(p);
	}
	names.insert(NPair(name, o));
}

void* Desktop::getName(string name) {
	NIter p = names.find(name);
	if (p == names.end()) {
		return NULL;
	}
	return p->second;
}

bool Desktop::checkBounce(int id, int msg) {
    TIter p = touches.find(id);
    if (TouchPad::isTouchDown(msg)) {
        if (p != touches.end()) return true;
        touches.insert(id);
    } else {
        if (p == touches.end()) return true;
        if (TouchPad::isTouchUp(msg)) {
            touches.erase(p);
        }
    }
    return false;
}

void Desktop::update(uint64 timestamp) {
    currentTimestamp = timestamp;
	if (isChanged) {
		getScreenSizes();
	}
	int cnt = touchPad.getTouchCount();
	if (cnt > 0) {
		for (int i = 0; i < MAX_TOUCHES; i++) {
			Touch* t = touchPad.getTouch(i);
			if (t->isActive) {
				int msg = (cnt > 1)?emtMultiTouchUp:emtSingleTouchUp;
				if (t->isMoved) {
					msg = (cnt > 1)?emtMultiTouchMove:emtSingleTouchMove;
				}
				if (t->isPressed) {
					msg = (cnt > 1)?emtMultiTouchDown:emtSingleTouchDown;
				}
                if (!checkBounce(t->id, msg)) {
                    if (currentScene != NULL) {
    		    	    currentScene->sendMessage(msg | (t->id & emtTouchIdMask), t->x, t->y);
	    		    }
                }
			}
		}
	}
	if (isKeyAvailable) {
		s3eKeyboardUpdate();
	}
	if (currentScene != NULL) {
		currentScene->update(timestamp);
	}
}

void Desktop::refresh() {
	if (currentScene != NULL) {
		currentScene->refresh();
	}
}

void Desktop::startMusic(const char* res) {
	if (s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3) &&
		s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_PCM))
        s3eAudioPlay(res, 0);
}

void Desktop::stopMusic() {
	s3eAudioStop();
}

bool Desktop::isQuitMessageReceived() {
	if (s3eDeviceCheckQuitRequest()) {
		return true;
	}
	return IsQuitMessageReceived;
}
