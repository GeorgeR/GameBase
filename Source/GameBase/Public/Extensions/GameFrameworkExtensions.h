#pragma once

#include "CoreMinimal.h"

class GAMEBASE_API FGameFrameworkExtensions
{
public:
	template <typename T>
	static T* GetGameModeAs(UObject* WorldContextObject);

	template <typename T>
	static T* GetGameInstanceAs(UObject* WorldContextObject);

	template <typename T>
	static T* GetGameStateAs(UObject* WorldContextObject);

	template <typename T>
	static T* GetLevelScriptActorAs(UObject* WorldContextObject);

	template <typename T>
	static T* GetPlayerStateAs(UObject* WorldContextObject);

	template <typename T>
	static T* GetPlayerControllerAs(UObject* WorldContextObject);

	template <typename T>
	static T* GetWorldSettingsAs(UObject* WorldContextObject);
};

template <typename T>
T* FGameFrameworkExtensions::GetGameModeAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	return Cast<T>(UGameplayStatics::GetGameMode(WorldContextObject));
}

template <typename T>
T* FGameFrameworkExtensions::GetGameInstanceAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	return Cast<T>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

template <typename T>
T* FGameFrameworkExtensions::GetGameStateAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	return WorldContextObject->GetWorld()->GetGameState<T>();
}

template <typename T>
T* FGameFrameworkExtensions::GetLevelScriptActorAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	return Cast<T>(WorldContextObject->GetWorld()->GetLevelScriptActor());
}

template <typename T>
T* FGameFrameworkExtensions::GetPlayerStateAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	const auto PlayerController = GetPlayerControllerAs<APlayerController>(WorldContextObject);
	if (PlayerController == nullptr)
		return nullptr;

	return Cast<T>(PlayerController->PlayerState);
}

template <typename T>
T* FGameFrameworkExtensions::GetPlayerControllerAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	T* Result = nullptr;

	auto GameInstance = GetGameInstanceAs<UGameInstance>(WorldContextObject);
	if (GameInstance == nullptr)
		Result = Cast<T>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
	else
	{
		Result = Cast<T>(GameInstance->GetFirstLocalPlayerController(WorldContextObject->GetWorld()));
		if (Result == nullptr)
			Result = Cast<T>(GameInstance->GetPrimaryPlayerController());

		if (Result == nullptr)
			Result = Cast<T>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
	}

	return Result;
}

template <typename T>
T* FGameFrameworkExtensions::GetWorldSettingsAs(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	return Cast<T>(WorldContextObject->GetWorld()->GetWorldSettings());
}
