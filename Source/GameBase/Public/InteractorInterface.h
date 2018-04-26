#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractorInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IInteractorInterface
{
	GENERATED_BODY()

public:
	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool TryInteract(const TScriptInterface<class IInteractableInterface>& InInteractive);*/

	/* Test for interaction (to get mouse over like effects) but don't actually perform it, this should be on tick. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool TestInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool TryInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	FVector GetTraceOrigin();
};