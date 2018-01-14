#pragma once

#include "DamageDealerInterface.h"
#include "WeaponAmmunitionInterface.h"
#include "WeaponInfoInterface.h"
#include "WeaponInfo.h"

#include "DamageInfo.generated.h"

class UWeaponAmmunition;

USTRUCT(BlueprintType)
struct GAMEBASE_API FDamageInfo
{
	GENERATED_BODY()

public:
	FDamageInfo() { }
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TScriptInterface<IDamageDealerInterface> Dealer;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FWeaponInfo Weapon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Damage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Force;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector Location;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Falloff;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Range;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Spread;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsExplosive;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	uint8 DamageType;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TScriptInterface<IWeaponAmmunitionInterface> Ammunition;

	template <typename TAmmunition>
	TAmmunition* GetAmmunitionAs();

	bool TryHit(UWorld* InWorld, FHitResult& OutHit);

	template <typename TDamageType>
	void SetDamageType(TDamageType InDamageType);

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