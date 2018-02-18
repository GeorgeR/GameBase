#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageInfo.h"

#include "Projectile.generated.h"

class IDamageDealerInterface;

/* Based on Tom Looman's Survival Game TakeHitInfo. */
USTRUCT(BlueprintType)
struct GAMEBASE_API FDamageHit
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FDamageEvent DamageEvent;

	UPROPERTY()
	FPointDamageEvent PointDamageEvent;

	UPROPERTY()
	FRadialDamageEvent RadialDamageEvent;

public:
	UPROPERTY()
	TScriptInterface<IDamageDealerInterface> Dealer;

	UPROPERTY()
	float Damage;

	UPROPERTY()
	uint8 DamageEventClassID;
	
	FDamageHit()
		: Dealer(nullptr),
		Damage(0.0f) { }
	
	FDamageEvent& GetDamageEvent();
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHit, FDamageHit&, InHit);

/* Parameters needed for a projectile. */
USTRUCT(BlueprintType)
struct GAMEBASE_API FProjectileParams
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FDamageInfo DamageInfo;

	UPROPERTY()
	FVector Start;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	TArray<AActor*> IgnoredActors;

	inline const FVector GetEnd() const { return Start + (Direction * GetRange()); }
	inline const float GetRange() const { return DamageInfo.Range; }

	FProjectileParams() { }
	FProjectileParams(FDamageInfo& InDamageInfo, FVector InStart, FVector InDirection);
};

/* An actual projectile actor, similar to UE4's own implementation. */
UCLASS(Abstract)
class GAMEBASE_API AProjectile 
	: public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* Movement;

public:
	AProjectile();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FDamageInfo DamageInfo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bShouldBounce;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsHoming;

	void Initialize(float InInitialSpeed);

	void SetHomingTarget(AActor* InActor);

	void OnComponentHit_Implementation(UPrimitiveComponent* InHitComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComponent, FVector InNormalImpulse, const FHitResult& OutHit);

	FOnHit& GetOnHit() { return OnHit; }

private:
	FOnHit OnHit;
};