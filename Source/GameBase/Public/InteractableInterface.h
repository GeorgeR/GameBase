#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"

#include "InteractableInterface.generated.h"

class IInteractorInterface;

UINTERFACE(Blueprintable, BlueprintType)
class UInteractableInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IInteractableInterface
{
	GENERATED_BODY()

public:
	/** Checks if the Interactor can actually interact with this item */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool CanInteract(const TScriptInterface<IInteractorInterface>& Interactor, const FHitResult& Hit) const;
	virtual bool CanInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactor, const FHitResult& Hit) const = 0;

	/** Perform the interaction */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool TryInteract(const TScriptInterface<IInteractorInterface>& Interactor, const FHitResult& Hit);
	virtual bool TryInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactor, const FHitResult& Hit) = 0;
};
