#include "BulletProjectileSpawner.h"
#include "DrawDebugHelpers.h"

void UBulletProjectileSpawner::Fire_Implementation(const FProjectileParams& Params)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActors(Params.IgnoredActors);
	CollisionParams.bTraceAsyncScene = true;
	CollisionParams.bReturnPhysicalMaterial = true;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Params.Start, Params.GetEnd(), ECollisionChannel::ECC_Camera, CollisionParams))
	{
		DrawDebugLine(GetWorld(), Params.Start, HitResult.Location, FColor::Red, false, 1.0f);
		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 16, FColor::Red, false, 1.0f);

		if (GetOnHit().IsBound())
		{
			/*FDamageHit Hit(Params.DamageInfo, Params.Direction, HitResult);
			GetOnHit().Execute(Hit);*/
		}
	}
}