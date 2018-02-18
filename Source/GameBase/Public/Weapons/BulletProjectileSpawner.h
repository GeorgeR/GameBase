#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileSpawnerInterface.h"

#include "BulletProjectileSpawner.generated.h"

/* A bullet spawner rather than a projectile. Does a linecast rather than spawning a physical projectile. */
UCLASS(BlueprintType)
class GAMEBASE_API UBulletProjectileSpawner
	: public UObject,
	public IProjectileSpawnerInterface
{
	GENERATED_BODY()

public:
	virtual void Fire_Implementation(const FProjectileParams& Params) override;
	virtual FOnHit GetOnHit_Implementation() override { return OnHit; }

private:
	FOnHit OnHit;
};