#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileSpawnerInterface.h"

#include "BulletProjectileSpawner.generated.h"

UCLASS(BlueprintType)
class GAMEBASE_API UBulletProjectileSpawner
	: public UObject,
	public IProjectileSpawnerInterface
{
	GENERATED_BODY()

public:
	virtual void Fire(const FProjectileParams& Params) override;
	virtual FOnHit& GetOnHit() override { return OnHit; }

private:
	FOnHit OnHit;
};