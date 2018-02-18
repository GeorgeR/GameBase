#pragma once

#include "CoreMinimal.h"

#include "WeaponAmmunitionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponAmmunitionInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* Stores information for weapon ammunition and damage types. */
class GAMEBASE_API IWeaponAmmunitionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	uint8 GetAmmoType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	uint8 GetDamageType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	float GetSpeed();
};