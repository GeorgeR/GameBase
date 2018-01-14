#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpawnerInterface.h"

#include "ProjectileSpawner.generated.h"

UCLASS()
class UProjectileSpawner
	: public UObject,
	public IProjectileSpawnerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSubclassOf<AProjectile> ProjectileClass;

	virtual void Fire(const FProjectileParams& Params) override;
	virtual FOnHit& GetOnHit() override { return OnHit; }

protected:
	template <typename T>
	T* SpawnProjectile(FVector InStart, FVector InDirection, float InSpeed);

private:
	FOnHit OnHit;
};

template <typename T>
T* UProjectileSpawner::SpawnProjectile(FVector InStart, FVector InDirection, float InSpeed)
{
	FRotator Rotation = InDirection.Rotation();
	return GetWorld()->SpawnActor<T>(ProjectileClass, InStart, Rotation);
}