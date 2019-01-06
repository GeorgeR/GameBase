#include "ActorExtensionsBP.h"

#include "ActorExtensions.h"
#include "GameFramework/Actor.h"

UObject* UActorExtensions::GetActorOrComponent(const AActor* Actor, const TSubclassOf<UObject> Class)
{
	// TODO
	return nullptr;
}

void UActorExtensions::GetBoundsPoints(const AActor* Actor, TArray<FVector>& Vertices)
{
	return FActorExtensions::GetBoundsPoints(Actor, Vertices);
}
