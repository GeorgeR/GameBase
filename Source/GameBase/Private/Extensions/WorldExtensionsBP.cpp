#include "WorldExtensionsBP.h"

#include "WorldExtensions.h"
#include "Engine/PostProcessVolume.h"

AActor* UWorldExtensions::GetFirst(UObject* WorldContextObject, TSubclassOf<UObject> Class)
{
	// TODO:


	return nullptr;
}

APostProcessVolume* UWorldExtensions::GetMainPostProcessVolume(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	auto World = WorldContextObject->GetWorld();

	static TKeyValuePair<UWorld*, APostProcessVolume*> Cached(nullptr, nullptr);
	if (Cached.Key != nullptr && Cached.Key == World && Cached.Value != nullptr)
		return Cached.Value;

	auto PostProcessVolume = FWorldExtensions::GetFirst<APostProcessVolume>(WorldContextObject, [](APostProcessVolume* PostProcessVolume) -> bool {
		return PostProcessVolume->ActorHasTag(TEXT("Main"));
	});

	if (PostProcessVolume != nullptr)
	{
		Cached = { World, PostProcessVolume };
		return Cached.Value;
	}

	return nullptr;
}
