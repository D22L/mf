#include "SoundAction.h"
#include "Desktop.h"

SoundAction::SoundAction(AbstractScreenObject* sprite, uint64 timeDelta, 
									 const char* r, int loc): AnimateAction(sprite, timeDelta, timeDelta)
									 , res(r), loc(loc) {
}

void SoundAction::doAction(int timeDelta) {
	CIwResGroup* resGroup;
	const char* groupName = Locale::getGroupName(loc);
	if (checkSound() &&(groupName != NULL)) {
	    resGroup = IwGetResManager()->GetGroupNamed(groupName);
		CIwSoundSpec* SoundSpec = (CIwSoundSpec*)resGroup->GetResNamed(res.c_str(), IW_SOUND_RESTYPE_SPEC);
		CIwSoundInst* SoundInstance = SoundSpec->Play();
	}
}

bool SoundAction::checkSound() {
	IObject* o = (IObject*)desktop.getName("soundon");
	if (o != NULL) {
		return (o->getState() != 0);
	}
	return false;
}
