#include "DamageInfo.h"

bool FDamageInfo::TryHit(UWorld* InWorld, FHitResult& OutHit)
{
	FVector End = Location + (Direction * Range);
	return InWorld->LineTraceSingleByChannel(OutHit, Location, End, ECollisionChannel::ECC_Camera);
}