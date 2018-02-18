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
	/* Create and return the tracing ray for the object. For a player this is usually the center of the screen pointing forwards. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void GetTracingRay(FVector& OutOrigin, FVector& OutDirection);
};