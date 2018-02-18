#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "TargetPointComponent.generated.h"

/* A user or procedurally placed component to help AI targeting. */
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