#include "VAudioWindowsHandler.h"
#if _VOID_USE_WINMM_
#include "../../AudioFormat/VAudioFormat.h"
#include "../../../Utility/Logger/VLogger.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
	// VAudioWindowsHandler
	//----------------------------------------------------------------------------------------------------
	VAudioWindowsHandler::VAudioWindowsHandler()
	{

	}

	//----------------------------------------------------------------------------------------------------
	VAudioWindowsHandler::VAudioWindowsHandler(const VAudioWindowsHandler& _handler)
	{

	}

	//----------------------------------------------------------------------------------------------------
	std::map<int, VAudioDevice> VAudioWindowsHandler::LoadDevice()
	{
		// Input
		WAVEINCAPS waveInCaps;
		int inputCount = waveInGetNumDevs();
		for (int i = 0; i < inputCount; ++i)
		{
			waveInGetDevCaps(i, &waveInCaps, sizeof(WAVEINCAPS));
		}

		// Output
		WAVEOUTCAPS waveOutCaps;
		int ouputCount = waveOutGetNumDevs();
		for (int i = 0; i < ouputCount; ++i)
		{
			waveOutGetDevCaps(i, &waveOutCaps, sizeof(WAVEINCAPS));
		}

		return std::map<int, VAudioDevice>();
	}

	//----------------------------------------------------------------------------------------------------
	int VAudioWindowsHandler::DefaultInputDeviceId()
	{

		return -1;
	}

	//----------------------------------------------------------------------------------------------------
	int VAudioWindowsHandler::DefaultOutputDeviceId()
	{

		return -1;
	}

	// Test
	//----------------------------------------------------------------------------------------------------
	void VAudioWindosHandlerTest()
	{

		return;
	}

}

#endif
