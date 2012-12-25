#include "Scene.h"
#include "Desktop.h"

Scene::Scene(): AbstractSpriteOwner()
              , isInitialized(false)
              , background(NULL)
              , keys()
              , IsPaused(false)
              , pauseTimestamp(0)
              , lastTime(0) {
//	regKey(s3eKeyLSK);
	regKey(s3eKeyBack);
	regKey(s3eKeyAbsBSK);
}

bool Scene::init() {
	bool r = !isInitialized;
	isInitialized = true;
	return r;
}

int Scene::getXSize(int xSize) {
	if (background != NULL) {
		return (getDesktopWidth() * xSize) / background->getWidth();
	}
	return xSize;
}

int Scene::getYSize(int ySize) {
	if (background != NULL) {
		return (getDesktopHeight() * ySize) / background->getHeight();
	}
	return ySize;
}

void Scene::refresh() {
    init();
	if (background == NULL) {
		for (ZIter p = zOrder.begin(); p != zOrder.end(); ++p) {
			if (p->second->isBackground()) {
				background = p->second;
				break;
			}
		}
	}
	AbstractSpriteOwner::refresh();
}

void Scene::regKey(s3eKey key) {
	keys.insert(KPair(key, 0));
}

void Scene::update(uint64 timestamp, bool) {
	if (IsPaused && (pauseTimestamp == 0)) {
		pauseTimestamp = pauseTimestamp;
	}
	if (!IsPaused && (pauseTimestamp != 0)) {
		uint64 pauseDelta = timestamp - pauseTimestamp;
		if (pauseDelta > 0) {
			correctPauseDelta(pauseDelta);
		}
		pauseTimestamp = 0;
	}
	for (KIter p = keys.begin(); p != keys.end(); ++p) {
		int msg = 0;
		int32 keyState = s3eKeyboardGetState(p->first);
		if (keyState & (S3E_KEY_STATE_DOWN | S3E_KEY_STATE_PRESSED)) {
			msg = emtKeyDown;
			if (p->second == 0) {
				msg = emtKeyPressed;
				p->second = 1;
			}
		}
		if (keyState == S3E_KEY_STATE_UP) {
			if (p->second == 1) {
				msg = emtKeyReleased;
				p->second = 0;
			}
		}
		if (msg != 0) {
            if (doKeyMessage(msg, p->first)) {
                lastTime = timestamp;
            } else {
                if (timestamp - lastTime >= 1000) {
                    lastTime = 0;
                }
                if ((lastTime == 0)&&(msg == emtKeyPressed)) {
                    switch (p->first) {
//                      case s3eKeyLSK:
                        case s3eKeyBack:
                        case s3eKeyAbsBSK:
                                desktop.sendQuitMessage();
                                break;
                    }
                }
            }
		}
	}
	AbstractSpriteOwner::update(timestamp, IsPaused);
}

bool Scene::sendMessage(int id, int x, int y) {
	if (AbstractSpriteOwner::sendMessage(id, x, y)) {
		return true;
	}
	if (IsPaused) return false;
	if (background != NULL) {
		return background->sendMessage(id, x, y);
	}
	return false;
}

void Scene::suspend() {
	desktop.suspend();
	IsPaused = true;
}

void Scene::resume() {
	desktop.resume();
	IsPaused = false;
}
