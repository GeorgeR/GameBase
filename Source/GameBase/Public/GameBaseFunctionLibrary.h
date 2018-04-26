#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObjectIterator.h"
#include "Engine/PostProcessVolume.h"
#include "EngineUtils.h"

#include "GameBaseFunctionLibrary.generated.h"

UCLASS(BlueprintType)
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

	/* Returns the first object - the actor or one of it's components that implements or inherits TClass */
	template <typename TClass>
	static TClass* GetActorOrComponent(AActor* InActor, UObject*& OutObject);

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

	UFUNCTION(BlueprintCallable, Category = "GameBase", meta = (WorldContext = "InWorldContextObject"))
	static APostProcessVolume* GetMainPostProcessVolume(UObject* InWorldContextObject);

	template <typename TActor>
	static void ForEachActor(UObject* InWorldContextObject, TFunction<void(TActor*)> InFunc);

	template <typename TComponent>
	static bool ForEachComponent(AActor* InActor, TFunction<void(TComponent*)> InFunc);

	template <typename TClass>
	static TArray<TClass*> FindAllInherited(TSubclassOf<TClass> InBaseClass);

	template <typename TEnum1, typename TEnum2>
	static bool HasFlag(TEnum1 InValue, TEnum2 InFlag) { return ((InValue & StaticCast<uint8>(InFlag))) == StaticCast<uint8>(InFlag); }

	template <typename TEnum1, typename TEnum2>
	static bool HasntFlag(TEnum1 InValue, TEnum2 InFlag) { return ((InValue & StaticCast<uint8>(InFlag))) == 0; }

	template <typename TEnum1, typename TEnum2>
	static void AddFlag(TEnum1 InValue, TEnum2 InFlag) { return InValue |= StaticCast<uint8>(InFlag); }

	template <typename TEnum1, typename TEnum2>
	static void RemoveFlag(TEnum1 InValue, TEnum2 InFlag) { InValue &= ~StaticCast<uint8>(InFlag); }

#pragma region Silly functions that will probably be moved
	template <typename T>
	TArray<T> Splice(TArray<T>& InSource, int32 InStart, int32 InEnd);

	FBox Encompass(const FBox& InSource, const FVector& InPoint) const;

	FBox Encompass(const FBox& InSource, const FBox& InOther) const;
#pragma endregion Silly functions that will probably be moved
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

	const auto PlayerController = GetPlayerControllerAs<APlayerController>(InWorldContextObject);
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
TArray<TComponent*> UGameBaseFunctionLibrary::GetComponents(const AActor* InActor)
{
	check(InActor);

	TArray<TComponent*> Result;
	TArray<UActorComponent*> Components = InActor->GetComponentsByClass(TComponent::StaticClass());
	if (Components.Num() == 0)
		return Result;

	for (auto Component : Components)
		Result.Add(Cast<TComponent>(Component));

	return Result;
}

template<typename TClass>
inline TClass * UGameBaseFunctionLibrary::GetActorOrComponent(AActor* InActor, UObject*& OutObject)
{
	auto Result = Cast<TClass>(InActor);
	if (Result != nullptr)
	{
		OutObject = InActor;
		return Result;
	}
	
	TSet<UActorComponent*> Components = InActor->GetComponents();
	for (auto& Component : Components)
	{
		Result = Cast<TClass>(Component);
		if (Result != nullptr)
		{
			OutObject = Component;
			return Result;
		}
	}

	return nullptr;
}

template <typename T>
FName UGameBaseFunctionLibrary::GetEnumName(const FName InEnumName, const T InValue)
{
	const auto Enum = FindObject<UEnum>(ANY_PACKAGE, *InEnumName.ToString(), true);
	check(Enum);
	if (Enum == nullptr)
		return TEXT("");

	auto EnumName = Enum->GetFName().ToString();
	EnumName.RemoveFromStart(TEXT("E"), ESearchCase::CaseSensitive);
	const auto UppercaseChars = GetUppercaseChars(EnumName);

	auto ValueName = Enum->GetNameStringByIndex(StaticCast<uint8>(InValue));
	ValueName.RemoveFromStart(UppercaseChars + TEXT("_"));
	const FName Result = *ValueName;

	return Result;
}

template <typename TActor>
void UGameBaseFunctionLibrary::ForEachActor(UObject* InWorldContextObject, TFunction<void(TActor*)> InFunc)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	for (TActorIterator<TActor> Iterator(InWorldContextObject->GetWorld()); Iterator; ++Iterator)
		InFunc(*Iterator);
}

template <typename TComponent>
bool UGameBaseFunctionLibrary::ForEachComponent(AActor* InActor, TFunction<void(TComponent*)> InFunc)
{
	check(InActor);

	TComponent* Component = Cast<TComponent>(InActor->GetComponentByClass(TComponent::StaticClass()));
	if (Component == nullptr)
		return false;

	InFunc(Component);

	return true;
}

template <typename TClass>
TArray<TClass*> UGameBaseFunctionLibrary::FindAllInherited(TSubclassOf<TClass> InBaseClass)
{
	TArray<TClass*> Result;
	for(TObjectIterator<TClass> Iterator; Iterator; ++Iterator)
	{
		UClass* Class = *Iterator;
		if (!Class->IsNative())
			continue;

		if (Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists))
			continue;

#if WITH_EDITOR
		if(FKismetEditorUtilities::IsClassABlueprintSkeleton(Class))
			continue;;
#endif

		if (!Class->IsChildOf(InBaseClass))
			continue;

		Result.Add(Class);
	}

	return Result;
}

template <typename T>
TArray<T> UGameBaseFunctionLibrary::Splice(TArray<T>& InSource, int32 InStart, int32 InEnd)
{
	TArray<T> Result;
	Result.Append(InSource.GetData()[InStart], InEnd - InStart);
	return Result;
}
