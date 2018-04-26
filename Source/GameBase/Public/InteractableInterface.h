#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "InteractableInterface.generated.h"

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool TestInteract(const TScriptInterface<class IInteractorInterface>& InInteractor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool CanInteract(const TScriptInterface<class IInteractorInterface>& InInteractor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void Interact(const TScriptInterface<class IInteractorInterface>& InInteractor);
};