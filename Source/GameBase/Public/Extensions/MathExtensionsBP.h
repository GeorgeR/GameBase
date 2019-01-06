#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MathExtensionsBP.generated.h"

UCLASS(BlueprintType)
class GAMEBASE_API UMathExtensions
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase|Math")
	static void FitViewToBounds(const FBox& Bounds, float& FOV, FTransform& Transform);
};
