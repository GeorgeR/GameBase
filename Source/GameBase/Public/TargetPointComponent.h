#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "TargetPointComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEBASE_API UTargetPointComponent 
	: public USceneComponent
{
	GENERATED_BODY()

public:
	UTargetPointComponent();

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	UBillboardComponent* Sprite;
#endif
};