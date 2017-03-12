#pragma once
#ifndef _V_MEMORYLEAKDETECTOR_H_
#define _V_MEMORYLEAKDETECTOR_H_

#include "../../VDefine.h"
#ifdef _VOID_ENABLE_MEMORYLEAKDETECTOR_
#if defined(WIN32) || defined(WIN64) || defined(_WIN32_WCE)

//----------------------------------------------------------------------------------------------------
int before_main();
int after_main();

//----------------------------------------------------------------------------------------------------
#pragma data_seg(".CRT$XIU")
static int(*before[])() = { before_main };
#pragma data_seg(".CRT$XPU")
static int(*after[])() = { after_main };
#pragma data_seg()

#else
//----------------------------------------------------------------------------------------------------
#endif
#endif

#endif
