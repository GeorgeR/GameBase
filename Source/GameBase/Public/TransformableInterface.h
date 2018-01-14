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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool IsMoving();
};