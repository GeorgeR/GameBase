#pragma once

#include "CoreMinimal.h"

#include "WeaponAmmunitionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponAmmunitionInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IWeaponAmmunitionInterface
{
	GENERATED_BODY()

public:
	virtual uint8 GetAmmoType() = 0;
	virtual uint8 GetDamageType() = 0;
	virtual const float GetSpeed() const = 0;
};