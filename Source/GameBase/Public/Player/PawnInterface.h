#pragma once

#include "CoreMinimal.h"

#include "PawnInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPawnInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IPawnInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase|Pawn")
	virtual UCameraComponent* GetCamera() = 0;

	UFUNCTION(BlueprintCallable, Category = "GameBase|Pawn")
	virtual float GetDefaultFOV() = 0;
};