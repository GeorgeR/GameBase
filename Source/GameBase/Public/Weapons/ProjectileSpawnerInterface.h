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

/* Generic projectile spawner, can fire and returns an event when hit. */
/* #todo Need a way of associating a hit with a fire call. */
class GAMEBASE_API IProjectileSpawnerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	void Fire(const FProjectileParams& Params);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	FOnHit GetOnHit();
};
