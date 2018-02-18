#pragma once

#include "CoreMinimal.h"

#include "TargetableInterface.generated.h"

class UTargetPointComponent;

UINTERFACE(MinimalAPI)
class UTargetableInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API ITargetableInterface
{
	GENERATED_BODY()

public:
	/* Get pre-placed target points, useful for AI */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void GetTargetPoints(UPARAM(ref) TArray<UTargetPointComponent*>& OutPoints);

	/* Check if this can hit the target even if it requires turning */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool CanHit(FVector InStartPoint, float InRange, UTargetPointComponent*& OutPoint);

	/* Checks if the incoming ray is facing this object */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool IsFacing(FVector InPoint, FVector InDirection);

	/* Checks if the incoming ray is facing the target point */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool IsFacingPoint(FVector InPoint, FVector InDirection, UTargetPointComponent* InTarget);
};