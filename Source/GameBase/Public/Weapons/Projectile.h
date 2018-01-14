#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageInfo.h"

#include "Projectile.generated.h"

struct FDamageHit;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHit, FDamageHit&);

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

USTRUCT(BlueprintType)
struct GAMEBASE_API FDamageHit
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FDamageInfo DamageInfo;

	UPROPERTY()
	AActor* Actor;

	UPROPERTY()
	UPrimitiveComponent* Component;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	FVector Normal;

	FDamageHit() { }
	FDamageHit(const FDamageInfo& InDamageInfo, FVector InDirection, const FHitResult& InHitResult);
};

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

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* InHitComponent, AActor* InOtherActor, UPrimitiveComponent* InOtherComponent, FVector InNormalImpulse, const FHitResult& OutHit);

	FOnHit& GetOnHit() { return OnHit; }

private:
	FOnHit OnHit;
};