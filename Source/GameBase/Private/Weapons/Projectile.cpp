#include "Projectile.h"
#include "Weapons/ProjectileSpawnerInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

FProjectileParams::FProjectileParams(FDamageInfo& InDamageInfo, FVector InStart, FVector InDirection)
	: DamageInfo(InDamageInfo),
	Start(InStart),
	Direction(InDirection) { }

FDamageHit::FDamageHit(const FDamageInfo& InDamageInfo, FVector InDirection, const FHitResult& InHitResult)
	: DamageInfo(InDamageInfo)
{
	Actor = InHitResult.GetActor();
	Component = InHitResult.GetComponent();
	Location = InHitResult.Location;
	Direction = InDirection;
	Normal = InHitResult.Normal;
}

AProjectile::AProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(5.0f);
	Sphere->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	Sphere->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHit);
	Sphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	Sphere->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	RootComponent = Sphere;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->UpdatedComponent = Sphere;
	Movement->InitialSpeed = 3000.0f;
	Movement->MaxSpeed = 3000.0f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = bShouldBounce;
	Movement->bIsHomingProjectile = bIsHoming;
}

void AProjectile::Initialize(float InInitialSpeed)
{
	Movement->InitialSpeed = InInitialSpeed;
}

void AProjectile::SetHomingTarget(AActor* InActor)
{
	Movement->HomingTargetComponent = InActor->GetRootComponent();
}

void AProjectile::OnComponentHit(UPrimitiveComponent* InHitComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComponent, FVector InNormalImpulse, const FHitResult& OutHit)
{
	FDamageHit Hit(DamageInfo, InNormalImpulse, OutHit);
	GetOnHit().Broadcast(Hit);
}