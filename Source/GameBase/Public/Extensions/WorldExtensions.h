#pragma once

#include "EngineUtils.h"
#include "CoreMinimal.h"

class GAMEBASE_API FWorldExtensions
{
public:
	template <typename TActor>
	static void ForEachActor(UObject* WorldContextObject, TFunction<void(TActor*)> Func);

	template <typename TActor>
	static TActor* GetFirst(UObject* WorldContextObject);

	template <typename TActor>
	static TActor* GetFirst(UObject* WorldContextObject, TFunction<bool(TActor*)> Func);

	template <typename TType>
	static TArray<TType*> FindAllInherited(TSubclassOf<TType> BaseClass);
};

template <typename TActor>
void FWorldExtensions::ForEachActor(UObject* WorldContextObject, TFunction<void(TActor*)> Func)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	for (TActorIterator<TActor> Iterator(WorldContextObject->GetWorld()); Iterator; ++Iterator)
		Func(*Iterator);
}

template <typename TActor>
TActor* FWorldExtensions::GetFirst(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	for (TActorIterator<TActor> Iterator(WorldContextObject->GetWorld()); Iterator; ++Iterator)
		return *Iterator;

	return nullptr;
}

template <typename TActor>
TActor* FWorldExtensions::GetFirst(UObject* WorldContextObject, TFunction<bool(TActor*)> Func)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	for (TActorIterator<TActor> Iterator(WorldContextObject->GetWorld()); Iterator; ++Iterator)
		if (Func(*Iterator))
			return *Iterator;

	return nullptr;
}

template <typename TType>
static TArray<TType*> FWorldExtensions::FindAllInherited(TSubclassOf<TType> BaseClass)
{
	TArray<TType*> Result;
	for (TObjectIterator<TType> Iterator; Iterator; ++Iterator)
	{
		UClass* Class = *Iterator;
		if (!Class->IsNative())
			continue;

		if (Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists))
			continue;

#if WITH_EDITOR
		if (FKismetEditorUtilities::IsClassABlueprintSkeleton(Class))
			continue;;
#endif

		if (!Class->IsChildOf(BaseClass))
			continue;

		Result.Add(Class);
	}

	return Result;
}
