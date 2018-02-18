#pragma once

#include "WeaponInfo.generated.h"

class UWeaponInterface;

/* Generic weapon info, useful when you need UI info and not the actual actor. */
USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UWeaponInterface> WeaponClass;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UTexture2D* Icon;
};