#pragma once

#include "CoreMinimal.h"

#include "ExtendedClassInterface.generated.h"

UINTERFACE(MinimalAPI)
class UExtendedClassInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* If you have user implementations of a class, use this to choose which takes precedence by order. */
class GAMEBASE_API IExtendedClassInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	int32 GetOrder();
};