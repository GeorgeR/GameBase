#pragma once

#include "Weapons/DamageInfo.h"
#include "Weapons/Projectile.h"

#include "DamageReceiverInterface.generated.h"

class IDamageDealerInterface;
class UDamageType;

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDamageReceiverDamaged, const TScriptInterface<IDamageDealerInterface>&, DamageDealer, const class UDamageType*, DamageType, float, InDamage);
DECLARE_DYNAMIC_DELEGATE(FOnDamageReceiverDestroyed);

UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class UDamageReceiverInterface
	: public UInterface
{
	GENERATED_BODY()
};

/* This object can receive damage. */
class GAMEBASE_API IDamageReceiverInterface
{
	GENERATED_BODY()

public:
//	/* Applies damage to this object. */
//	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
//#if WITH_ABILITIES
//	float TakeDamage(float Damage, const FHitResult& Hit, const struct FGameplayTagContainer& Tags, const TScriptInterface<IDamageDealerInterface>& DamageDealer, AActor* Causer);
//#else
//	float TakeDamage(const TScriptInterface<IDamageDealerInterface>& DamageDealer, const UDamageType* DamageType, float InDamage);
//#endif

	/* Returns an event for when this object takes damage. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	FOnDamageReceiverDamaged GetOnDamageReceiverDamaged();

	/* Returns the hitpoints of this object, given a part enum (optional). You might separate head from torso damage, for example. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	int32 GetHitPoints(uint8 InPart = 0);

	/* Returns the maximum hitpoints of an object, given an optional part. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	int32 GetMaxHitPoints(uint8 InPart = 0);

	/* Returns true if this object or part (optional) has armor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	bool HasArmor(uint8 InPart = 0);

	/* Returns the armor points of a given part (optional), if any. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	int32 GetArmorPoints(uint8 InPart = 0);

	/* Returns the maximum armor points of a given part (optional), if any. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	int32 GetMaxArmorPoints(uint8 InPart = 0);

	/* Return true if this object is destroyed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	bool IsDestroyed();

	/* Returns an event for when this object is destroyed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	FOnDamageReceiverDestroyed GetOnDamageReceiverDestroyed();
};

UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class UDamageReceiverPrivateInterface
	: public UInterface
{
	GENERATED_BODY()
};

/* This object can receive damage. */
class GAMEBASE_API IDamageReceiverPrivateInterface
{
	GENERATED_BODY()

public:
	/* When the HitPoints <= 0 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	void Kill();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	void Suicide();

	/* This is more of a reminder to have a replicated property in this object. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	struct FDamageHit GetLastHitInfo() const;
};
