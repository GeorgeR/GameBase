#include "Weapons/ProjectileSpawner.h"
#include "Weapons/ProjectileSpawnerInterface.h"
#include "Weapons/Projectile.h"

void UProjectileSpawner::Fire(const FProjectileParams& Params)
{
	AProjectile* Projectile = SpawnProjectile<AProjectile>(Params.Start, Params.Direction, Params.DamageInfo.Ammunition->GetSpeed());
	Projectile->GetOnHit().AddLambda([&](FDamageHit& Hit) -> void {
		if (GetOnHit().IsBound())	
			GetOnHit().Broadcast(Hit);
		
		Projectile->Destroy();
	});
}