#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "ObserverComponent.generated.h"

/* Transforms/attaches itself to the player at runtime and in editor. */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEBASE_API UObserverComponent
    : public USceneComponent
{
    GENERATED_BODY()

public:
    UObserverComponent();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
    static USceneComponent* GetCharacterTransform(const UObject* WorldContextObject);
};