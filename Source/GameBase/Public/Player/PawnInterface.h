#pragma once

#include "CoreMinimal.h"

#include "PawnInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UPawnInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* A generic interface for a pawn. */
class GAMEBASE_API IPawnInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Pawn")
	UCameraComponent* GetCamera();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Pawn")
	float GetDefaultFOV();
};