#pragma once

#include "CoreMinimal.h"
#include "DamageDealerInterface.h"

#include "FiringInterface.generated.h"

UINTERFACE(MinimalAPI)
class UFiringInterface 
	: public UInterface
{
	GENERATED_BODY()
};

/* A generic interface for an object/actor that can fire. */
class GAMEBASE_API IFiringInterface
{
	GENERATED_BODY()

public:
	/* Checks if the specified dealer can fire this object. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	bool CanFire(const TScriptInterface<IDamageDealerInterface>& InDamageDealer) const;

	/* Checks and returns if this object is firing. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	bool IsFiring() const;

	/* Start firing for the given damage dealer. The interface owner is usually the weapon and not the actual wielder so we need this parameter. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	void StartFire(const TScriptInterface<IDamageDealerInterface>& InDamageDealer);

	/* Stops firing. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	void StopFire();

	/* Usually called internally when StartFire is called. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	void Fire();
};