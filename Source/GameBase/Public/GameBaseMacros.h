#pragma once

#include "CoreMinimal.h"

#if DO_CHECK && !USING_CODE_ANALYSIS

// @todo: document why these are needed?
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || \
    (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define __FUNC__ __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define __FUNC__ __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define __FUNC__ __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || \
    (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define __FUNC__ __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define __FUNC__ __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define __FUNC__ __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define __FUNC__ __func__
#else
#define __FUNC__ "(unknown)"
#endif

/** Descriptive specialization of unimplemented() macro **/
#define unimplementedFunction() checkf(false, TEXT("Unimplemented Function: %s"), TEXT(__FUNC__))

/** use native unimplemented() macro **/
//#define notImplemented(InFormat, ...) UE_ENSURE_IMPL(&, true, false, InFormat, ##__VA_ARGS__)

#endif
