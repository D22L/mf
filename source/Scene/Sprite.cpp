#include "Sprite.h"
#include "Locale.h"
#include "Desktop.h"

Sprite::Sprite(ISpriteOwner* owner, int x, int y , int zOrder): AbstractScreenObject(x, y)
														    , owner(owner)
															, capturedId(-1)
                                                            , img(NULL) {
    owner->addSprite((AbstractScreenObject*)this, zOrder);
}

Sprite::Sprite(ISpriteOwner* owner, const char* res, int x, int y, int zOrder, int locale): AbstractScreenObject(x, y)
														    , owner(owner)
															, capturedId(-1)
                                                            , img(NULL) {
    addImage(res, 0, locale);
    owner->addSprite((AbstractScreenObject*)this, zOrder);
}

bool Sprite::sendMessage(int msg, uint64 timestamp, void* data) {
	return owner->sendMessage(msg, timestamp, data);
}

bool Sprite::sendMessage(int msg, int x, int y) {
	if ((msg & emtTouchEvent) != emtTouchEvent) return false;
	if (!isVisible) return false;
	int id = msg & emtTouchIdMask;
	msg &= emtTouchMask;
	if (capturedId >= 0) {
		if (msg == emtTouchDown) {
			capturedId = -1;
		}
	} 
    bool isOut = false;
    int X = owner->getXSize(owner->getXPos(getXPos()));
	int Y = owner->getYSize(owner->getYPos(getYPos()));
	if ((x < X)||(y < Y)) {
        isOut = true;
    }
    X += owner->getXSize(getWidth());
	Y += owner->getYSize(getHeight());
	if ((x > X)||(y > Y)) {
        isOut = true;
    }
    if (isOut) {
       if (capturedId < 0) {
           return false;
  	   }
       msg |= emtTouchOut;
    }
	switch (msg) {
		case emtTouchDown:
			capturedId = id;
			break;
		case emtTouchUp:
			capturedId = -1;
			break;
	}
	if (isBuzy()) {
		return true;
	}
	return sendMessage(msg) || 
		   owner->sendMessage(msg);
}

void Sprite::addImage(const char*res, int state, int loc) {
	img = rm.load(res, loc);
}

CIw2DImage* Sprite::getImage(int id) {
	return img->getData();
}

int Sprite::getWidth() {
	CIw2DImage* img = getImage(getState());
	if (img != NULL) {
		return img->GetWidth();
	} else {
		return 0;
	}
}

int Sprite::getHeight() {
	CIw2DImage* img = getImage(getState());
	if (img != NULL) {
		return img->GetHeight();
	} else {
		return 0;
	}
}

void Sprite::unload() {
	if (img != NULL) {
		img->unload();
	}
}

void Sprite::refresh() {
	init();
	CIw2DImage* img = getImage(getState());
	if (isVisible && (img != NULL)) {
		CIwMat2D m;
		iwangle a = getAngle();
		if (a != 0) {
			a = IW_ANGLE_FROM_DEGREES(a);
		}
		int targetWidth  = owner->getXSize(getWidth());
		int targetHeight = owner->getYSize(getHeight());
		m.SetRot(a);
		m.ScaleRot(IW_GEOM_ONE);
		m.SetTrans(CIwSVec2(owner->getXSize(owner->getXPos(getXPos())), owner->getYSize(owner->getYPos(getYPos()))));
		Iw2DSetTransformMatrix(m);
		Iw2DSetAlphaMode(alpha);
		Iw2DDrawImage(img, CIwSVec2(0, 0), CIwSVec2(targetWidth, targetHeight));
	}
}
