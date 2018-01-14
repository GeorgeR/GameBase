#pragma once

#include "WeaponInfo.generated.h"

class AWeaponActor;

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UClass* Class;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UTexture2D* Icon;
};