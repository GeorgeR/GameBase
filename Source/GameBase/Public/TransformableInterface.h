#pragma once

#include "CoreMinimal.h"

#include "TransformableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTransformableInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API ITransformableInterface
{
	GENERATED_BODY()

public:
	/* Returns true if the object can *ever* move. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool CanMove() const;

	/* Returns true if the object is currently moving. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool IsMoving();
};