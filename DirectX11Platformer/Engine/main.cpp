////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;
	
	
	//Create the system object
	System = new SystemClass;
	if(!System)
	{
		return 0;
	}

	//Initialise and run system
	result = System->Initialise();
	if(result)
	{
		System->Run();
	}

	//Shutdown and release the system
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}