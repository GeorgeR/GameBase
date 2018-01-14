#pragma once

#include "CoreMinimal.h"

#include "ExtendedClassInterface.generated.h"

UINTERFACE(MinimalAPI)
class UExtendedClassInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IExtendedClassInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	int32 GetOrder();
};