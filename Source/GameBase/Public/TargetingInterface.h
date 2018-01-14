#pragma once

#include "CoreMinimal.h"

#include "TargetingInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTargetingInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API ITargetingInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void GetTracingRay(FVector& OutOrigin, FVector& OutDirection);
};