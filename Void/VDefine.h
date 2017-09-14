#pragma once
#ifndef _V_DEFINE_H_
#define _V_DEFINE_H_

// Platform
//----------------------------------------------------------------------------------------------------
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

#if defined(TARGET_OS_MAC)
#define _VOID_MACOS_
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN32_WCE)
#define _VOID_WINDOWS_
#endif

// OpenGL
//----------------------------------------------------------------------------------------------------
//#define _VOID_DISABLE_OPENGL_

// Memory
//----------------------------------------------------------------------------------------------------
//#define _VOID_ENABLE_DEBUG_
#define _VOID_ENABLE_MEMORYLEAKDETECTOR_

// Audio
//----------------------------------------------------------------------------------------------------
// MacOS
#define _VOID_ENABLE_COREAUDIO_

#endif
