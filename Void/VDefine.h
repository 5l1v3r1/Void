#pragma once
#ifndef _V_DEFINE_H_
#define _V_DEFINE_H_

// Platform
//----------------------------------------------------------------------------------------------------
#ifdef __APPLE__
#include <TargetConditionals.h>
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
