#pragma once

#include "CoreMinimal.h"

#include "MapList.generated.h"

UENUM(BlueprintType)
enum class EMapOrder : uint8
{
	MO_InOrder = 0		UMETA(DisplayName = "In Order"),
	MO_Random = 1		UMETA(DisplayName = "Random")
};

/* A convenient object for specifying a map queue. */
USTRUCT(BlueprintType)
struct GAMEBASE_API FMapList
{
	GENERATED_BODY()

public:
	FMapList();

	UPROPERTY(BlueprintReadOnly)
	EMapOrder Order;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentMapIndex;

	UPROPERTY(BlueprintReadOnly)
	TArray<FName> MapNames;

	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FName> MapPaths;

	FName GetNextMap();
	void ResolveMapPaths();
};