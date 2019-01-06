#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class GAMEBASE_API FActorExtensions
{
public:
	template <typename TComponent>
	FORCEINLINE static TComponent* GetComponentOfType(const AActor* Actor);

	template <typename TComponent>
	static TArray<TComponent*> GetComponentsOfType(const AActor* Actor);

	/* Returns the first object - the actor or one of it's components that implements or inherits TType */
	template <class TType>
	static TType* GetActorOrComponent(AActor* Actor, UObject*& Object);

	static void GetBoundsPoints(const AActor* Actor, TArray<FVector>& Vertices);

	template <typename TComponent>
	static bool ForEachComponent(AActor* Actor, TFunction<void(TComponent*)> Func);
};

template <typename TComponent>
TComponent* FActorExtensions::GetComponentOfType(const AActor* Actor)
{
	check(Actor);

	return Cast<TComponent>(Actor->GetComponentByClass(TComponent::StaticClass()));
}

template <typename TComponent>
static TArray<TComponent*> FActorExtensions::GetComponentsOfType(const AActor* Actor)
{
	check(Actor);

	TArray<TComponent*> Result;
	auto Components = Actor->GetComponentsByClass(TComponent::StaticClass());
	if (Components.Num() == 0)
		return Result;

	for (auto Component : Components)
		Result.Add(Cast<TComponent>(Component));

	return Result;
}

// BUG: Doesn't work for interfaces
template <class TType>
TType* FActorExtensions::GetActorOrComponent(AActor* Actor, UObject*& Object)
{
	check(Actor);

	if (TIsIInterface<TType>::Value)
	{
		if (Actor->Implements<TType>())
		{
			Object = Actor;
			return Cast<TType>(Object);
		}

		TSet<UActorComponent*> Components = Actor->GetComponentsOfType();
		for (auto& Component : Components)
		{
			if (Component->Implements<TType>())
			{
				Object = Component;
				return Cast<TType>(Object);
			}
		}

		return nullptr;
	}
	else
	{
		auto Result = Cast<TType>(Actor);
		if (Result != nullptr)
		{
			Object = Actor;
			return Result;
		}

		TSet<UActorComponent*> Components = Actor->GetComponentsOfType();
		for (auto& Component : Components)
		{
			Result = Cast<TType>(Component);
			if (Result != nullptr)
			{
				Object = Component;
				return Result;
			}
		}

		return nullptr;
	}
}

template <typename TComponent>
bool FActorExtensions::ForEachComponent(AActor* Actor, TFunction<void(TComponent*)> Func)
{
	check(Actor);

	TComponent* Component = Cast<TComponent>(Actor->GetComponentByClass(TComponent::StaticClass()));
	if (Component == nullptr)
		return false;

	Func(Component);

	return true;
}
