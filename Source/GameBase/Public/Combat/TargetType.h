#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "TargetType.generated.h"

class ACharacter;
class AActor;
struct FHitResult;
struct FGameplayEventData;

UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class GAMEBASE_API UTargetType
	: public UObject
{
	GENERATED_BODY()

public:
	UTargetType() { }

	/*UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ACharacter* TargettingCharacter, AActor* TargettingActor, FGameplayEventData EventData, TArray<FHitResult>& HitResults, TArray<AActor*> Actors) const;*/
};
