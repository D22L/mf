#include "Main.h"

#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "IwSound.h"

#include "ResourceManager.h"
#include "DataManager.h"
#include "TouchPad.h"
#include "Desktop.h"
#include "Intro.h"

void init() {
	dm.init();

	// Initialise Mamrlade graphics system and Iw2D module
	IwGxInit();
    Iw2DInit();

	// Init IwSound
	IwSoundInit();

	// Set the default background clear colour
	IwGxSetColClear(0x0, 0x0, 0x0, 0);

	// Initialise the resource manager
	rm.init();

	touchPad.init();
	desktop.init();
}

void release() {
	dm.release();
	desktop.release();
	touchPad.release();

	// Shut down the resource manager
	rm.release();

	Iw2DTerminate();
	IwGxTerminate();
}

int main() {
	init();	{ 

        Intro  intro;
		desktop.setScene(&intro);

		int32 duration = 1000 / 25;
		// Main Game Loop
		while (!desktop.isQuitMessageReceived()) {
			// Update keyboard system
			s3eKeyboardUpdate();
		    // Update Iw Sound Manager
		    IwGetSoundManager()->Update();
			// Update
			touchPad.update();
			uint64 timestamp = s3eTimerGetMs();
			desktop.update(timestamp);
			// Clear the screen
			IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
			touchPad.clear();
			// Refresh
			desktop.refresh();
			// Show the surface
			Iw2DSurfaceShow();
			// Yield to the opearting system
			s3eDeviceYield(duration);
		}
	}
	release();
    return 0;
}
