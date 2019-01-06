#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractorInterface.generated.h"

class IInteractableInterface;

UINTERFACE(MinimalAPI)
class UInteractorInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* Contains the minimum information and Interactable needs to test if the caller can ... call it */
/* See LineCastInteractor for an example */
class GAMEBASE_API IInteractorInterface
{
	GENERATED_BODY()

public:
	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool TryInteract(const TScriptInterface<class IInteractableInterface>& InInteractive);*/

	/* Test for interaction (to get mouse over like effects) but don't actually perform it, this should be on tick. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool TestInteract(TScriptInterface<IInteractableInterface>& Interactable);
	virtual bool TestInteract_Implementation(TScriptInterface<IInteractableInterface>& Interactable) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool TryInteract(TScriptInterface<IInteractableInterface>& Interactable);
	virtual bool TryInteract_Implementation(TScriptInterface<IInteractableInterface>& Interactable) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool GetTransform(FVector& Location, FRotator& Rotation, FVector& Direction) const;
	virtual bool GetTransform_Implementation(FVector& Location, FRotator& Rotation, FVector& Direction) const = 0;
};
