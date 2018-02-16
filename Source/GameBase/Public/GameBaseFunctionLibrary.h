#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameBaseFunctionLibrary.generated.h"

#define HasFlag(Value, Flag) (((Value & static_cast<uint8>(Flag))) == static_cast<uint8>(Flag))
#define AddFlag(Value, Flag) Value |= static_cast<uint8>(Flag)
#define RemoveFlag(Value, Flag) Value &= ~static_cast<uint8>(Flag)

UCLASS()
class GAMEBASE_API UGameBaseFunctionLibrary 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	template <typename T>
	static T* GetGameModeAs(UObject* InWorldContextObject);

	template <typename T>
	static T* GetGameInstanceAs(UObject* InWorldContextObject);

	template <typename T>
	static T* GetGameStateAs(UObject* InWorldContextObject);

	template <typename T>
	static T* GetLevelScriptActorAs(UObject* InWorldContextObject);

	template <typename T>
	static T* GetPlayerStateAs(UObject* InWorldContextObject);

	template <typename T>
	static T* GetPlayerControllerAs(UObject* InWorldContextObject);

	template <typename T>
	static T* GetWorldSettingsAs(UObject* InWorldContextObject);

	template <typename TComponent>
	static TComponent* GetComponent(const AActor* InActor);

	template <typename TComponent>
	static TArray<TComponent*> GetComponents(const AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "GameBase", meta = (WorldContext = "InWorldContextObject"))
	static FVector2D GetMousePosition(UObject* InWorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "GameBase", meta = (WorldContext = "InWorldContextObject"))
	static bool GetMouseRay(UObject* InWorldContextObject, FVector& OutStart, FVector& OutDirection);

	UFUNCTION(BlueprintCallable, Category = "GameBase", meta = (WorldContext = "InWorldContextObject"))
	static void GetCenterScreenRay(UObject* InWorldContextObject, FVector& OutStart, FVector& OutDirection);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	static bool GetScreenspaceBounds(APlayerController* InPlayerController, AActor* InActor, FBox2D& OutBounds);

	template <typename T>
	static FName GetEnumName(const FName InEnumName, const T InValue);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	static void FitViewToBounds(const FBox& InBounds, float& InFOV, FTransform& InOutTransform);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	static FString GetUppercaseChars(FString InString);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	static void GetBoundsPoints(AActor* InActor, TArray<FVector>& OutVertices);

	template <typename TComponent>
	static bool ForComponent(AActor* InActor, TFunction<void(TComponent*)> InFunc);

	template <typename T>
	TArray<T> Splice(TArray<T>& InSource, int32 InStart, int32 InEnd);

	FBox Encompass(const FBox& InSource, const FVector& InPoint);

	FBox Encompass(const FBox& InSource, const FBox& InOther);
};

template <typename T>
T* UGameBaseFunctionLibrary::GetGameModeAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	return Cast<T>(UGameplayStatics::GetGameMode(InWorldContextObject));
}

template <typename T>
T* UGameBaseFunctionLibrary::GetGameInstanceAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	return Cast<T>(UGameplayStatics::GetGameInstance(InWorldContextObject));
}

template <typename T>
T* UGameBaseFunctionLibrary::GetGameStateAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	return InWorldContextObject->GetWorld()->GetGameState<T>();
}

template <typename T>
T* UGameBaseFunctionLibrary::GetLevelScriptActorAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	return Cast<T>(InWorldContextObject->GetWorld()->GetLevelScriptActor());
}

template <typename T>
T* UGameBaseFunctionLibrary::GetPlayerStateAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	APlayerController* PlayerController = GetPlayerControllerAs<APlayerController>(InWorldContextObject);
	if (PlayerController == nullptr)
		return nullptr;

	return Cast<T>(PlayerController->PlayerState);
}

template <typename T>
T* UGameBaseFunctionLibrary::GetPlayerControllerAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	T* Result = nullptr;

	UGameInstance* GameInstance = GetGameInstanceAs<UGameInstance>(InWorldContextObject);
	if (GameInstance == nullptr)
		Result = Cast<T>(UGameplayStatics::GetPlayerController(InWorldContextObject, 0));
	else
	{
		Result = Cast<T>(GameInstance->GetFirstLocalPlayerController(InWorldContextObject->GetWorld()));
		if (Result == nullptr)
			Result = Cast<T>(GameInstance->GetPrimaryPlayerController());

		if (Result == nullptr)
			Result = Cast<T>(UGameplayStatics::GetPlayerController(InWorldContextObject, 0));
	}

	return Result;
}

template <typename T>
T* UGameBaseFunctionLibrary::GetWorldSettingsAs(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	return Cast<T>(InWorldContextObject->GetWorld()->GetWorldSettings());
}

template <typename TComponent>
TComponent* UGameBaseFunctionLibrary::GetComponent(const AActor* InActor)
{
	check(InActor);

	return Cast<TComponent>(InActor->GetComponentByClass(TComponent::StaticClass()));
}

template <typename TComponent>
static TArray<TComponent*>
UGameBaseFunctionLibrary::GetComponents(const AActor* InActor)
{
	check(InActor);

	TArray<TComponent*> Result;
	TArray<UActorComponent*> Components;
	for (auto Component : Components)
		Result.Add(Cast<TComponent>(Component));

	return Result;
}

template <typename T>
FName UGameBaseFunctionLibrary::GetEnumName(const FName InEnumName, const T InValue)
{
	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *InEnumName.ToString(), true);
	check(Enum);
	if (Enum == nullptr)
		return TEXT("");

	FString EnumName = Enum->GetFName().ToString();
	EnumName.RemoveFromStart(TEXT("E"), ESearchCase::CaseSensitive);
	FString UppercaseChars = GetUppercaseChars(EnumName);

	FString ValueName = Enum->GetNameStringByIndex(static_cast<uint8>(InValue));
	ValueName.RemoveFromStart(UppercaseChars + TEXT("_"));
	FName Result = *ValueName;

	return Result;
}

template <typename TComponent>
bool UGameBaseFunctionLibrary::ForComponent(AActor* InActor, TFunction<void(TComponent*)> InFunc)
{
	check(InActor);

	TComponent* Component = Cast<TComponent>(InActor->GetComponentByClass(TComponent::StaticClass()));
	if (Component == nullptr)
		return false;

	InFunc(Component);

	return true;
}

template <typename T>
TArray<T> UGameBaseFunctionLibrary::Splice(TArray<T>& InSource, int32 InStart, int32 InEnd)
{
	TArray<T> Result;
	Result.Append(InSource.GetData()[InStart], InEnd - InStart);
	return Result;
}