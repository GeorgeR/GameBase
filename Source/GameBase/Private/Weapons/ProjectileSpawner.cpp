#include "Weapons/ProjectileSpawner.h"
#include "Weapons/ProjectileSpawnerInterface.h"
#include "Weapons/Projectile.h"

void UProjectileSpawner::Fire_Implementation(const FProjectileParams& Params)
{
	AProjectile* Projectile = SpawnProjectile<AProjectile>(Params.Start, Params.Direction, IWeaponAmmunitionInterface::Execute_GetSpeed(Params.DamageInfo.Ammunition.GetObject()));

	Projectile->GetOnHit().BindUFunction(this, TEXT("OnHit"));
	//Projectile->GetOnHit().AddLambda([&](FDamageHit& Hit) -> void {
	//	if (GetOnHit().IsBound())	
	//		GetOnHit().Broadcast(Hit);
	//	
	//	Projectile->Destroy();
	//});
}

void UProjectileSpawner::OnHit(FDamageHit& InHit)
{
	if (GetOnHit().IsBound())
		GetOnHit().Execute(InHit);
}