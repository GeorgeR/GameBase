#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "InteractableInterface.generated.h"

class IInteractorInterface;

UINTERFACE(MinimalAPI)
class UInteractableInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IInteractableInterface
{
	GENERATED_BODY()

public:
	/* For mouse-over highlighting */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool TestInteract(const TScriptInterface<IInteractorInterface>& Interactor) const;
	virtual bool TestInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactor) const = 0;

	/* Checks if the Interactor can actually interact with this item */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool CanInteract(const TScriptInterface<IInteractorInterface>& Interactor) const;
	virtual bool CanInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactor) const = 0;

	/* Perform the interaction */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	void Interact(const TScriptInterface<IInteractorInterface>& Interactor);
	virtual void Interact_Implementation(const TScriptInterface<IInteractorInterface>& Interactor) = 0;
};
