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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool TryInteract(const TScriptInterface<class IInteractableInterface>& InInteractive);
};