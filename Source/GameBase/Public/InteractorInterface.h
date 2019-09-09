#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractorInterface.generated.h"

class IInteractableInterface;

UINTERFACE(Blueprintable, BlueprintType)
class UInteractorInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IInteractorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Interaction")
	bool GetTransform(FVector& Location, FRotator& Rotation, FVector& Direction) const;
	virtual bool GetTransform_Implementation(FVector& Location, FRotator& Rotation, FVector& Direction) const { return false; }
};
