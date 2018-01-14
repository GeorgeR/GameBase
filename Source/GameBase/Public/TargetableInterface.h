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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	void GetTargetPoints(UPARAM(ref) TArray<UTargetPointComponent*>& OutPoints);

	/** Check if this can hit the target even if it requires turning **/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool CanHit(FVector InStartPoint, float InRange, UTargetPointComponent*& OutPoint);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool IsFacing(FVector InPoint, FVector InDirection);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool IsFacingPoint(FVector InPoint, FVector InDirection, UTargetPointComponent* InTarget);
};