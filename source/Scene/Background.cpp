#include "Background.h"

Background::Background(ISpriteOwner* owner, const char* res, int zOrder, int locale): Sprite(owner, res, 0, 0, zOrder, locale) {}

void Background::refresh() {
	CIwMat2D m;
	m.SetRot(0);
	m.ScaleRot(IW_GEOM_ONE);
	m.SetTrans(CIwSVec2(0, 0));
	Iw2DSetTransformMatrix(m);
	Iw2DSetAlphaMode(alpha);
	Iw2DDrawImage(getImage(), CIwSVec2(0, 0), CIwSVec2(owner->getDesktopWidth(), owner->getDesktopHeight()));
}
