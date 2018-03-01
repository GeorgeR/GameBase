#pragma once

#include "CoreMinimal.h"

#include "HasDisplayNameInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHasDisplayNameInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IHasDisplayNameInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	FName GetDisplayName();
	virtual FName GetDisplayName_Implementation() { return FName(); }
};