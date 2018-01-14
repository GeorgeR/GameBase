#pragma once

#include "CoreMinimal.h"

#include "InteractiveInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractiveInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IInteractiveInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool CanInteract(APlayerState* InPlayer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void Interact(APlayerState* InPlayer);
};