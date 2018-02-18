#pragma once

#include "DamageDealerInterface.h"
#include "WeaponAmmunitionInterface.h"
#include "WeaponInfoInterface.h"
#include "WeaponInfo.h"

#include "DamageInfo.generated.h"

class UWeaponAmmunition;

/* Information about damage. Alternative to UE4's own DamageType. */
USTRUCT(BlueprintType)
struct GAMEBASE_API FDamageInfo
{
	GENERATED_BODY()

public:
	FDamageInfo() { }
	
	/* Pointer to the dealer. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TScriptInterface<IDamageDealerInterface> Dealer;
	
	/* Information about the weapon used to cause the damage. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FWeaponInfo Weapon;

	/* Actual damage caused. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Damage;

	/* The force dealt, if any. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Force;

	/* The hit location. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector Location;

	/* The hit direction (opposite of the normal). */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector Direction;

	/* Damage falloff, ie. if it was a grenade. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Falloff;

	/* Weapon/Ammunition range. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Range;

	/* Weapon/Ammunition spread. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Spread;

	/* Is this damage explosive? */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsExplosive;

	/* Returns the damagetype (usually an enum). */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	uint8 DamageType;
	
	/* Ammunition used. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TScriptInterface<IWeaponAmmunitionInterface> Ammunition;

	/* Convenience function to cast the ammunition to the given type. */
	template <typename TAmmunition>
	TAmmunition* GetAmmunitionAs();

	/* Initial hit test, not sure if it should be here! */
	bool TryHit(UWorld* InWorld, FHitResult& OutHit);

	/* Convenience function to set the damage type. */
	template <typename TDamageType>
	void SetDamageType(TDamageType InDamageType);

	/* Convenience function to get the damage type. */
	template <typename TDamageType>
	const TDamageType GetDamageType() const;
};

template <typename TAmmunition>
TAmmunition* FDamageInfo::GetAmmunitionAs()
{
	return Cast<TAmmunition>(Ammunition.GetObject());
}

template <typename TDamageType>
void FDamageInfo::SetDamageType(TDamageType InDamageType)
{
	DamageType = static_cast<uint8>(InDamageType);
}

template <typename TDamageType>
const TDamageType FDamageInfo::GetDamageType() const
{
	return static_cast<TDamageType>(DamageType);
}