#pragma once

#include "CoreMinimal.h"
#include "Templates/Casts.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCasts, Log, All);
DEFINE_LOG_CATEGORY(LogCasts);

//GAMEBASE_API void CastLog(const TCHAR* FromType, const TCHAR* ToType, ELogVerbosity::Type Verbosity);
#define CAST_LOG(FromType, ToType, Verbosity) UE_LOG(LogCasts, Verbosity, TEXT("Cast of %s to %s failed"), FromType, ToType)

/** Specialization of Cast that will print to log on failure **/
template <typename To, typename From>
FORCEINLINE To* CastMsg(From* Src /*, ELogVerbosity::Type Verbosity = ELogVerbosity::Warning*/)
{
	auto Result = Cast<To, From>(Src);
	if(!Result)
    {
		CAST_LOG(*Cast<UObject>(Src)->GetFullName(), *GetTypeName<To>(), Warning);
		return nullptr;
    }
	return Result;
}
