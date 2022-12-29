#include "TypeSupportApplication.h"
#include "Photon_lib.h"
#include "UIListener.h"

UIListener* gpUIListener;

void TypeSupportApplication::run(UIListener* pListener)
{
	delete gpUIListener;
	gpUIListener = pListener;

	CPhotonLib photonLib;
	photonLib.run();
	gpUIListener->onLibClosed();
	delete gpUIListener;
	gpUIListener = NULL;
}