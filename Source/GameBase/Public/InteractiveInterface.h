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
	bool CanInteract(AActor* InUser);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void Interact(AActor* InUser);
};