#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"

#include "ProjectileSpawnerInterface.generated.h"

class UWeaponAmmunition;

UINTERFACE(MinimalAPI)
class UProjectileSpawnerInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IProjectileSpawnerInterface
{
	GENERATED_BODY()

public:
	virtual void Fire(const FProjectileParams& Params) = 0;
	virtual FOnHit& GetOnHit() = 0;
};