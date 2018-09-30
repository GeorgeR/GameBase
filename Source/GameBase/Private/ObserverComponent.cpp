#include "ObserverComponent.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <ContentStreaming.h>

UObserverComponent::UObserverComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

void UObserverComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector Location;
#if WITH_EDITOR
    auto World = GetWorld();
    if (World == nullptr)
        return;

    if (!World->IsGameWorld())
    {
        if (IStreamingManager::Get().GetNumViews() > 0)
        {
            auto View = IStreamingManager::Get().GetViewInformation(0);
            Location = View.ViewOrigin;
        }
    }
    else
#endif
    {
        Location = GetCharacterTransform(this)->GetComponentLocation();
    }

    this->SetWorldLocation(Location);
}

USceneComponent* UObserverComponent::GetCharacterTransform(const UObject* WorldContextObject)
{
    static TWeakObjectPtr<ACharacter> Character;
    if (!Character.IsValid() || Character.IsStale())
        Character = UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0);

    auto Result = Character.Get();
    if (Result == nullptr)
        return nullptr;

    return Result->GetRootComponent();
}