#pragma once
#ifndef _V_AUDIOWINDOWSHANDLER_H_
#define _V_AUDIOWINDOWSHANDLER_H_

#include "../../../VDefine.h"
#if defined(_VOID_WINDOWS_)
#define _VOID_USE_WINMM_
#include "../VAudioHandler.h"
#include "../../AudioDevice/VAudioDevice.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm")
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioWindosHandler
	// OS: Windows
	// Library: Winmm
	//----------------------------------------------------------------------------------------------------
	class VAudioWindowsHandler : public VAudioHandler
	{
	public:
		//----------------------------------------------------------------------------------------------------
		VAudioWindowsHandler();
		VAudioWindowsHandler(const VAudioWindowsHandler& _handler);
		virtual ~VAudioWindowsHandler() {};

		//----------------------------------------------------------------------------------------------------
		virtual std::map<int, VAudioDevice> LoadDevice();
		virtual int DefaultInputDeviceId();
		virtual int DefaultOutputDeviceId();

	protected:
		//----------------------------------------------------------------------------------------------------

	};

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioWindosHandlerTest();
}

#endif
#endif
