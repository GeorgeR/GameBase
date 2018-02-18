#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpawnerInterface.h"

#include "ProjectileSpawner.generated.h"

/* Default implementation of a projectile spawner. */
UCLASS()
class UProjectileSpawner
	: public UObject,
	public IProjectileSpawnerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSubclassOf<AProjectile> ProjectileClass;

	virtual void Fire_Implementation(const FProjectileParams& Params) override;
	virtual FOnHit GetOnHit_Implementation() override { return OnHitEvent; }

protected:
	template <typename T>
	T* SpawnProjectile(FVector InStart, FVector InDirection, float InSpeed);

private:
	FOnHit OnHitEvent;

	UFUNCTION()
	void OnHit(FDamageHit& InHit);
};

template <typename T>
T* UProjectileSpawner::SpawnProjectile(FVector InStart, FVector InDirection, float InSpeed)
{
	FRotator Rotation = InDirection.Rotation();
	return GetWorld()->SpawnActor<T>(ProjectileClass, InStart, Rotation);
}